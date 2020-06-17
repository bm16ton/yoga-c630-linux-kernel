/*
 * Copyright (C) 2020 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "compiler.h"

/* NIR creates vectors as vecN ops, which we represent by a synthetic
 * BI_COMBINE instruction, e.g.:
 *
 *      v = combine x, y, z, w
 *
 * These combines need to be lowered by the pass in this file. Fix a given
 * source at component c.
 *
 * First suppose the source is SSA. If it is also scalar, then we may rewrite
 * the destination of the generating instruction (unique by SSA+scalar) to
 * write to v.c, and rewrite each of its uses to swizzle out .c instead of .x
 * (the original by scalar). If it is vector, there are two cases. If the
 * component c is `x`, we are accessing v.x, and each of the succeeding
 * components y, z... up to the last component of the vector are accessed
 * sequentially, then we may perform the same rewrite. If this is not the case,
 * rewriting would require more complex vector features, so we fallback on a
 * move.
 *
 * Otherwise is the source is not SSA, we also fallback on a move. We could
 * probably do better.
 */

static void
bi_combine_mov32(bi_context *ctx, bi_instruction *parent, unsigned comp, unsigned R)
{
        bi_instruction move = {
                .type = BI_MOV,
                .dest = R,
                .dest_type = nir_type_uint32,
                .dest_offset = comp,
                .src = { parent->src[comp] },
                .src_types = { nir_type_uint32 },
                .swizzle = { { parent->swizzle[comp][0] } }
        };

        bi_emit_before(ctx, parent, move);
}

static void
bi_combine_sel16(bi_context *ctx, bi_instruction *parent, unsigned comp, unsigned R)
{
        bi_instruction sel = {
                .type = BI_SELECT,
                .dest = R,
                .dest_type = nir_type_uint32,
                .dest_offset = comp >> 1,
                .src = { parent->src[comp], parent->src[comp + 1] },
                .src_types = { nir_type_uint16, nir_type_uint16 },
                .swizzle = { {
                        parent->swizzle[comp][0],
                        parent->swizzle[comp + 1][0],
                } }
        };

        bi_emit_before(ctx, parent, sel);
}

/* Gets the instruction generating a given source. Combine lowering is
 * accidentally O(n^2) right now because this function is O(n) instead of O(1).
 * If this pass is slow, this cost can be avoided in favour for better
 * bookkeeping. */

static bi_instruction *
bi_get_parent(bi_context *ctx, unsigned idx)
{
        bi_foreach_instr_global(ctx, ins) {
                if (ins->dest == idx)
                        return ins;
        }

        return NULL;
}

/* Rewrites uses of an index. Again, this could be O(n) to the program but is
 * currently O(nc) to the program and number of combines, so the pass becomes
 * effectively O(n^2). Better bookkeeping would bring down to linear if that's
 * an issue. */

static void
bi_rewrite_uses(bi_context *ctx,
                unsigned old, unsigned oldc,
                unsigned new, unsigned newc)
{
        bi_foreach_instr_global(ctx, ins) {
                bi_foreach_src(ins, s) {
                        if (ins->src[s] != old) continue;

                        for (unsigned i = 0; i < 16; ++i)
                                ins->swizzle[s][i] += (newc - oldc);

                        ins->src[s] = new;
                }
        }
}

/* Checks if we have a nicely aligned vector prefix */

static bool
bi_is_aligned_vec32(bi_instruction *combine, unsigned s, bi_instruction *io,
                unsigned *count)
{
        /* We only support prefixes */
        if (s != 0)
                return false;

        if (!(bi_class_props[io->type] & BI_VECTOR))
                return false;

        if (nir_alu_type_get_type_size(combine->dest_type) != 32)
                return false;

        if (nir_alu_type_get_type_size(io->dest_type) != 32)
                return false;

        unsigned components = io->vector_channels;

        /* Are we contiguous like that? */

        for (unsigned i = 0; i < components; ++i) {
                if (combine->src[i] != io->dest)
                        return false;

                if (combine->swizzle[i][0] != i)
                        return false;
        }

        /* We're good to go */
        *count = components;
        return true;
}

#if 0
/* Tries to lower a given source of a combine to an appropriate rewrite,
 * returning true if successful, and false with no changes otherwise. */

static bool
bi_lower_combine_src(bi_context *ctx, bi_instruction *ins, unsigned s, unsigned R,
                unsigned *vec_count)
{
        unsigned src = ins->src[s];

        /* We currently only handle SSA */

        if (!src) return false;
        if (src & (BIR_SPECIAL | PAN_IS_REG)) return false;

        /* We are SSA. Lookup the generating instruction. */
        unsigned bytes = nir_alu_type_get_type_size(ins->dest_type) / 8;

        bi_instruction *parent = bi_get_parent(ctx, src,
                         0xF << (ins->swizzle[s][0] * bytes));

        if (!parent) return false;

        /* We have a parent instuction, sanity check the typesize */
        unsigned pbytes = nir_alu_type_get_type_size(parent->dest_type) / 8;
        if (pbytes != bytes) return false;

        bool scalar = parent->vector_channels != 0;
        if (!(scalar || bi_is_aligned_vec(ins, s, parent, vec_count))) return false;

        if (!bi_shift_mask(parent, bytes * s)) return false;
        bi_rewrite_uses(ctx, parent->dest, 0, R, s);
        parent->dest = R;
        return true;
}
#endif

void
bi_lower_combine(bi_context *ctx, bi_block *block)
{
        bi_foreach_instr_in_block_safe(block, ins) {
                if (ins->type != BI_COMBINE) continue;

                unsigned R = bi_make_temp_reg(ctx);

                bi_foreach_src(ins, s) {
                        /* We're done early for vec2/3 */
                        if (!ins->src[s])
                                continue;

#if 0
                        unsigned vec_count = 0;

                        if (bi_lower_combine_src(ctx, ins, s, R, &vec_count)) {
                                /* Skip vectored sources */
                                if (vec_count)
                                        s += (vec_count - 1);
                        } else {
                                bi_insert_combine_mov(ctx, ins, s, R);
                        }
#endif
                        if (ins->dest_type == nir_type_uint32)
                                bi_combine_mov32(ctx, ins, s, R);
                        else {
                                bi_combine_sel16(ctx, ins, s, R);
                                s++;
                        }
                }


                bi_rewrite_uses(ctx, ins->dest, 0, R, 0);
                bi_remove_instruction(ins);
        }
}
