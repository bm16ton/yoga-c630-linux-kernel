/*
 * Copyright (C) 2017-2019 Alyssa Rosenzweig
 * Copyright (C) 2017-2019 Connor Abbott
 * Copyright (C) 2019 Collabora, Ltd.
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

#include <panfrost-job.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include "decode.h"
#include "util/macros.h"
#include "util/u_math.h"

#include "pan_pretty_print.h"
#include "midgard/disassemble.h"
#include "bifrost/disassemble.h"

#include "pan_encoder.h"

static void pandecode_swizzle(unsigned swizzle, enum mali_format format);

#define MEMORY_PROP(obj, p) {\
        if (obj->p) { \
                char *a = pointer_as_memory_reference(obj->p); \
                pandecode_prop("%s = %s", #p, a); \
                free(a); \
        } \
}

#define MEMORY_PROP_DIR(obj, p) {\
        if (obj.p) { \
                char *a = pointer_as_memory_reference(obj.p); \
                pandecode_prop("%s = %s", #p, a); \
                free(a); \
        } \
}

FILE *pandecode_dump_stream;

/* Semantic logging type.
 *
 * Raw: for raw messages to be printed as is.
 * Message: for helpful information to be commented out in replays.
 * Property: for properties of a struct
 *
 * Use one of pandecode_log, pandecode_msg, or pandecode_prop as syntax sugar.
 */

enum pandecode_log_type {
        PANDECODE_RAW,
        PANDECODE_MESSAGE,
        PANDECODE_PROPERTY
};

#define pandecode_log(...)  pandecode_log_typed(PANDECODE_RAW,      __VA_ARGS__)
#define pandecode_msg(...)  pandecode_log_typed(PANDECODE_MESSAGE,  __VA_ARGS__)
#define pandecode_prop(...) pandecode_log_typed(PANDECODE_PROPERTY, __VA_ARGS__)

unsigned pandecode_indent = 0;

static void
pandecode_make_indent(void)
{
        for (unsigned i = 0; i < pandecode_indent; ++i)
                fprintf(pandecode_dump_stream, "    ");
}

static void
pandecode_log_typed(enum pandecode_log_type type, const char *format, ...)
{
        va_list ap;

        pandecode_make_indent();

        if (type == PANDECODE_MESSAGE)
                fprintf(pandecode_dump_stream, "// ");
        else if (type == PANDECODE_PROPERTY)
                fprintf(pandecode_dump_stream, ".");

        va_start(ap, format);
        vfprintf(pandecode_dump_stream, format, ap);
        va_end(ap);

        if (type == PANDECODE_PROPERTY)
                fprintf(pandecode_dump_stream, ",\n");
}

static void
pandecode_log_cont(const char *format, ...)
{
        va_list ap;

        va_start(ap, format);
        vfprintf(pandecode_dump_stream, format, ap);
        va_end(ap);
}

/* To check for memory safety issues, validates that the given pointer in GPU
 * memory is valid, containing at least sz bytes. The goal is to eliminate
 * GPU-side memory bugs (NULL pointer dereferences, buffer overflows, or buffer
 * overruns) by statically validating pointers.
 */

static void
pandecode_validate_buffer(mali_ptr addr, size_t sz)
{
        if (!addr) {
                pandecode_msg("XXX: null pointer deref");
                return;
        }

        /* Find a BO */

        struct pandecode_mapped_memory *bo =
                pandecode_find_mapped_gpu_mem_containing(addr);

        if (!bo) {
                pandecode_msg("XXX: invalid memory dereference\n");
                return;
        }

        /* Bounds check */

        unsigned offset = addr - bo->gpu_va;
        unsigned total = offset + sz;

        if (total > bo->length) {
                pandecode_msg("XXX: buffer overrun. "
                                "Chunk of size %zu at offset %d in buffer of size %zu. "
                                "Overrun by %zu bytes. \n",
                                sz, offset, bo->length, total - bo->length);
                return;
        }
}

struct pandecode_flag_info {
        u64 flag;
        const char *name;
};

static void
pandecode_log_decoded_flags(const struct pandecode_flag_info *flag_info,
                            u64 flags)
{
        bool decodable_flags_found = false;

        for (int i = 0; flag_info[i].name; i++) {
                if ((flags & flag_info[i].flag) != flag_info[i].flag)
                        continue;

                if (!decodable_flags_found) {
                        decodable_flags_found = true;
                } else {
                        pandecode_log_cont(" | ");
                }

                pandecode_log_cont("%s", flag_info[i].name);

                flags &= ~flag_info[i].flag;
        }

        if (decodable_flags_found) {
                if (flags)
                        pandecode_log_cont(" | 0x%" PRIx64, flags);
        } else {
                pandecode_log_cont("0x%" PRIx64, flags);
        }
}

#define FLAG_INFO(flag) { MALI_##flag, "MALI_" #flag }
static const struct pandecode_flag_info gl_enable_flag_info[] = {
        FLAG_INFO(OCCLUSION_QUERY),
        FLAG_INFO(OCCLUSION_PRECISE),
        FLAG_INFO(FRONT_CCW_TOP),
        FLAG_INFO(CULL_FACE_FRONT),
        FLAG_INFO(CULL_FACE_BACK),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_CLEAR_##flag, "MALI_CLEAR_" #flag }
static const struct pandecode_flag_info clear_flag_info[] = {
        FLAG_INFO(FAST),
        FLAG_INFO(SLOW),
        FLAG_INFO(SLOW_STENCIL),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_MASK_##flag, "MALI_MASK_" #flag }
static const struct pandecode_flag_info mask_flag_info[] = {
        FLAG_INFO(R),
        FLAG_INFO(G),
        FLAG_INFO(B),
        FLAG_INFO(A),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_##flag, "MALI_" #flag }
static const struct pandecode_flag_info u3_flag_info[] = {
        FLAG_INFO(HAS_MSAA),
        FLAG_INFO(CAN_DISCARD),
        FLAG_INFO(HAS_BLEND_SHADER),
        FLAG_INFO(DEPTH_WRITEMASK),
        {}
};

static const struct pandecode_flag_info u4_flag_info[] = {
        FLAG_INFO(NO_MSAA),
        FLAG_INFO(NO_DITHER),
        FLAG_INFO(DEPTH_RANGE_A),
        FLAG_INFO(DEPTH_RANGE_B),
        FLAG_INFO(STENCIL_TEST),
        FLAG_INFO(SAMPLE_ALPHA_TO_COVERAGE_NO_BLEND_SHADER),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_MFBD_FORMAT_##flag, "MALI_MFBD_FORMAT_" #flag }
static const struct pandecode_flag_info mfbd_fmt_flag_info[] = {
        FLAG_INFO(MSAA),
        FLAG_INFO(SRGB),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_EXTRA_##flag, "MALI_EXTRA_" #flag }
static const struct pandecode_flag_info mfbd_extra_flag_hi_info[] = {
        FLAG_INFO(PRESENT),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_EXTRA_##flag, "MALI_EXTRA_" #flag }
static const struct pandecode_flag_info mfbd_extra_flag_lo_info[] = {
        FLAG_INFO(ZS),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_##flag, "MALI_" #flag }
static const struct pandecode_flag_info shader_midgard1_flag_lo_info [] = {
        FLAG_INFO(WRITES_Z),
        FLAG_INFO(EARLY_Z),
        FLAG_INFO(READS_TILEBUFFER),
        FLAG_INFO(READS_ZS),
        {}
};

static const struct pandecode_flag_info shader_midgard1_flag_hi_info [] = {
        FLAG_INFO(WRITES_S),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_MFBD_##flag, "MALI_MFBD_" #flag }
static const struct pandecode_flag_info mfbd_flag_info [] = {
        FLAG_INFO(DEPTH_WRITE),
        FLAG_INFO(EXTRA),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_SAMP_##flag, "MALI_SAMP_" #flag }
static const struct pandecode_flag_info sampler_flag_info [] = {
        FLAG_INFO(MAG_NEAREST),
        FLAG_INFO(MIN_NEAREST),
        FLAG_INFO(MIP_LINEAR_1),
        FLAG_INFO(MIP_LINEAR_2),
        FLAG_INFO(NORM_COORDS),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_SFBD_FORMAT_##flag, "MALI_SFBD_FORMAT_" #flag }
static const struct pandecode_flag_info sfbd_unk1_info [] = {
        FLAG_INFO(MSAA_8),
        FLAG_INFO(MSAA_A),
        {}
};
#undef FLAG_INFO

#define FLAG_INFO(flag) { MALI_SFBD_FORMAT_##flag, "MALI_SFBD_FORMAT_" #flag }
static const struct pandecode_flag_info sfbd_unk2_info [] = {
        FLAG_INFO(MSAA_B),
        FLAG_INFO(SRGB),
        {}
};
#undef FLAG_INFO

extern char *replace_fragment;
extern char *replace_vertex;

static char *
pandecode_job_type(enum mali_job_type type)
{
#define DEFINE_CASE(name) case JOB_TYPE_ ## name: return "JOB_TYPE_" #name

        switch (type) {
                DEFINE_CASE(NULL);
                DEFINE_CASE(WRITE_VALUE);
                DEFINE_CASE(CACHE_FLUSH);
                DEFINE_CASE(COMPUTE);
                DEFINE_CASE(VERTEX);
                DEFINE_CASE(TILER);
                DEFINE_CASE(FUSED);
                DEFINE_CASE(FRAGMENT);

        case JOB_NOT_STARTED:
                return "NOT_STARTED";

        default:
                pandecode_log("Warning! Unknown job type %x\n", type);
                return "!?!?!?";
        }

#undef DEFINE_CASE
}

static char *
pandecode_draw_mode(enum mali_draw_mode mode)
{
#define DEFINE_CASE(name) case MALI_ ## name: return "MALI_" #name

        switch (mode) {
                DEFINE_CASE(DRAW_NONE);
                DEFINE_CASE(POINTS);
                DEFINE_CASE(LINES);
                DEFINE_CASE(TRIANGLES);
                DEFINE_CASE(TRIANGLE_STRIP);
                DEFINE_CASE(TRIANGLE_FAN);
                DEFINE_CASE(LINE_STRIP);
                DEFINE_CASE(LINE_LOOP);
                DEFINE_CASE(POLYGON);
                DEFINE_CASE(QUADS);
                DEFINE_CASE(QUAD_STRIP);

        default:
                pandecode_msg("XXX: invalid draw mode %X\n", mode);
                return "";
        }

#undef DEFINE_CASE
}

#define DEFINE_CASE(name) case MALI_FUNC_ ## name: return "MALI_FUNC_" #name
static char *
pandecode_func(enum mali_func mode)
{
        switch (mode) {
                DEFINE_CASE(NEVER);
                DEFINE_CASE(LESS);
                DEFINE_CASE(EQUAL);
                DEFINE_CASE(LEQUAL);
                DEFINE_CASE(GREATER);
                DEFINE_CASE(NOTEQUAL);
                DEFINE_CASE(GEQUAL);
                DEFINE_CASE(ALWAYS);

        default:
                pandecode_msg("XXX: invalid func %X\n", mode);
                return "";
        }
}
#undef DEFINE_CASE

#define DEFINE_CASE(name) case MALI_STENCIL_ ## name: return "MALI_STENCIL_" #name
static char *
pandecode_stencil_op(enum mali_stencil_op op)
{
        switch (op) {
                DEFINE_CASE(KEEP);
                DEFINE_CASE(REPLACE);
                DEFINE_CASE(ZERO);
                DEFINE_CASE(INVERT);
                DEFINE_CASE(INCR_WRAP);
                DEFINE_CASE(DECR_WRAP);
                DEFINE_CASE(INCR);
                DEFINE_CASE(DECR);

        default:
                pandecode_msg("XXX: invalid stencil op %X\n", op);
                return "";
        }
}

#undef DEFINE_CASE

static char *pandecode_attr_mode_short(enum mali_attr_mode mode)
{
        switch(mode) {
                /* TODO: Combine to just "instanced" once this can be done
                 * unambiguously in all known cases */
        case MALI_ATTR_POT_DIVIDE:
                return "instanced_pot";
        case MALI_ATTR_MODULO:
                return "instanced_mod";
        case MALI_ATTR_NPOT_DIVIDE:
                return "instanced_npot";
        case MALI_ATTR_IMAGE:
                return "image";
        default:
                pandecode_msg("XXX: invalid attribute mode %X\n", mode);
                return "";
        }
}

static const char *
pandecode_special_record(uint64_t v, bool* attribute)
{
        switch(v) {
        case MALI_ATTR_VERTEXID:
                *attribute = true;
                return "gl_VertexID";
        case MALI_ATTR_INSTANCEID:
                *attribute = true;
                return "gl_InstanceID";
        case MALI_VARYING_FRAG_COORD:
                return "gl_FragCoord";
        case MALI_VARYING_FRONT_FACING:
                return "gl_FrontFacing";
        case MALI_VARYING_POINT_COORD:
                return "gl_PointCoord";
        default:
                pandecode_msg("XXX: invalid special record %" PRIx64 "\n", v);
                return "";
        }
}

#define DEFINE_CASE(name) case MALI_WRAP_## name: return "MALI_WRAP_" #name
static char *
pandecode_wrap_mode(enum mali_wrap_mode op)
{
        switch (op) {
                DEFINE_CASE(REPEAT);
                DEFINE_CASE(CLAMP_TO_EDGE);
                DEFINE_CASE(CLAMP_TO_BORDER);
                DEFINE_CASE(MIRRORED_REPEAT);

        default:
                pandecode_msg("XXX: invalid wrap mode %X\n", op);
                return "";
        }
}
#undef DEFINE_CASE

#define DEFINE_CASE(name) case MALI_BLOCK_## name: return "MALI_BLOCK_" #name
static char *
pandecode_block_format(enum mali_block_format fmt)
{
        switch (fmt) {
                DEFINE_CASE(TILED);
                DEFINE_CASE(UNKNOWN);
                DEFINE_CASE(LINEAR);
                DEFINE_CASE(AFBC);

        default:
                unreachable("Invalid case");
        }
}
#undef DEFINE_CASE

#define DEFINE_CASE(name) case MALI_EXCEPTION_ACCESS_## name: return ""#name
char *
pandecode_exception_access(unsigned access)
{
        switch (access) {
                DEFINE_CASE(NONE);
                DEFINE_CASE(EXECUTE);
                DEFINE_CASE(READ);
                DEFINE_CASE(WRITE);

        default:
                unreachable("Invalid case");
        }
}
#undef DEFINE_CASE

/* Midgard's tiler descriptor is embedded within the
 * larger FBD */

static void
pandecode_midgard_tiler_descriptor(
                const struct midgard_tiler_descriptor *t,
                unsigned width,
                unsigned height,
                bool is_fragment,
                bool has_hierarchy)
{
        pandecode_log(".tiler = {\n");
        pandecode_indent++;

        if (t->hierarchy_mask == MALI_TILER_DISABLED)
                pandecode_prop("hierarchy_mask = MALI_TILER_DISABLED");
        else
                pandecode_prop("hierarchy_mask = 0x%" PRIx16, t->hierarchy_mask);

        /* We know this name from the kernel, but we never see it nonzero */

        if (t->flags)
                pandecode_msg("XXX: unexpected tiler flags 0x%" PRIx16, t->flags);

        MEMORY_PROP(t, polygon_list);

        /* The body is offset from the base of the polygon list */
        //assert(t->polygon_list_body > t->polygon_list);
        unsigned body_offset = t->polygon_list_body - t->polygon_list;

        /* It needs to fit inside the reported size */
        //assert(t->polygon_list_size >= body_offset);

        /* Check that we fit */
        struct pandecode_mapped_memory *plist =
                pandecode_find_mapped_gpu_mem_containing(t->polygon_list);

        //assert(t->polygon_list_size <= plist->length);

        /* Now that we've sanity checked, we'll try to calculate the sizes
         * ourselves for comparison */

        unsigned ref_header = panfrost_tiler_header_size(width, height, t->hierarchy_mask, has_hierarchy);
        unsigned ref_size = panfrost_tiler_full_size(width, height, t->hierarchy_mask, has_hierarchy);

        if (!((ref_header == body_offset) && (ref_size == t->polygon_list_size))) {
                pandecode_msg("XXX: bad polygon list size (expected %d / 0x%x)\n",
                                ref_header, ref_size);
                pandecode_prop("polygon_list_size = 0x%x", t->polygon_list_size);
                pandecode_msg("body offset %d\n", body_offset);
        }

        /* The tiler heap has a start and end specified -- it should be
         * identical to what we have in the BO. The exception is if tiling is
         * disabled. */

        MEMORY_PROP(t, heap_start);
        assert(t->heap_end >= t->heap_start);

        struct pandecode_mapped_memory *heap =
                pandecode_find_mapped_gpu_mem_containing(t->heap_start);

        unsigned heap_size = t->heap_end - t->heap_start;

        /* Tiling is enabled with a special flag */
        unsigned hierarchy_mask = t->hierarchy_mask & MALI_HIERARCHY_MASK;
        unsigned tiler_flags = t->hierarchy_mask ^ hierarchy_mask;

        bool tiling_enabled = hierarchy_mask;

        if (tiling_enabled) {
                /* When tiling is enabled, the heap should be a tight fit */
                unsigned heap_offset = t->heap_start - heap->gpu_va;
                if ((heap_offset + heap_size) != heap->length) {
                        pandecode_msg("XXX: heap size %u (expected %zu)\n",
                                        heap_size, heap->length - heap_offset);
                }

                /* We should also have no other flags */
                if (tiler_flags)
                        pandecode_msg("XXX: unexpected tiler %X\n", tiler_flags);
        } else {
                /* When tiling is disabled, we should have that flag and no others */

                if (tiler_flags != MALI_TILER_DISABLED) {
                        pandecode_msg("XXX: unexpected tiler flag %X, expected MALI_TILER_DISABLED\n",
                                        tiler_flags);
                }

                /* We should also have an empty heap */
                if (heap_size) {
                        pandecode_msg("XXX: tiler heap size %d given, expected empty\n",
                                        heap_size);
                }

                /* Disabled tiling is used only for clear-only jobs, which are
                 * purely FRAGMENT, so we should never see this for
                 * non-FRAGMENT descriptors. */

                if (!is_fragment)
                        pandecode_msg("XXX: tiler disabled for non-FRAGMENT job\n");
        }

        /* We've never seen weights used in practice, but we know from the
         * kernel these fields is there */

        bool nonzero_weights = false;

        for (unsigned w = 0; w < ARRAY_SIZE(t->weights); ++w) {
                nonzero_weights |= t->weights[w] != 0x0;
        }

        if (nonzero_weights) {
                pandecode_log(".weights = { ");

                for (unsigned w = 0; w < ARRAY_SIZE(t->weights); ++w) {
                        pandecode_log_cont("%d, ", t->weights[w]);
                }

                pandecode_log("},");
        }

        pandecode_indent--;
        pandecode_log("}\n");
}

/* TODO: The Bifrost tiler is not understood at all yet */

static void
pandecode_bifrost_tiler_descriptor(const struct mali_framebuffer *fb)
{
        pandecode_log(".tiler = {\n");
        pandecode_indent++;

        MEMORY_PROP(fb, tiler_meta);

        for (int i = 0; i < 16; i++) {
                if (fb->zeros[i] != 0) {
                        pandecode_msg("XXX: tiler descriptor zero %d tripped, value %x\n",
                                      i, fb->zeros[i]);
                }
        }

        pandecode_log("},\n");

        pandecode_indent--;
        pandecode_log("}\n");

}

/* Information about the framebuffer passed back for
 * additional analysis */

struct pandecode_fbd {
        unsigned width;
        unsigned height;
        unsigned rt_count;
        bool has_extra;
};

static void
pandecode_sfbd_format(struct mali_sfbd_format format)
{
        pandecode_log(".format = {\n");
        pandecode_indent++;

        pandecode_log(".unk1 = ");
        pandecode_log_decoded_flags(sfbd_unk1_info, format.unk1);
        pandecode_log_cont(",\n");

        /* TODO: Map formats so we can check swizzles and print nicely */
        pandecode_log("swizzle");
        pandecode_swizzle(format.swizzle, MALI_RGBA8_UNORM);
        pandecode_log_cont(",\n");

        pandecode_prop("nr_channels = MALI_POSITIVE(%d)",
                       (format.nr_channels + 1));

        pandecode_log(".unk2 = ");
        pandecode_log_decoded_flags(sfbd_unk2_info, format.unk2);
        pandecode_log_cont(",\n");

        pandecode_prop("block = %s", pandecode_block_format(format.block));

        pandecode_prop("unk3 = 0x%" PRIx32, format.unk3);

        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_shared_memory(const struct mali_shared_memory *desc, bool is_compute)
{
        pandecode_prop("stack_shift = 0x%x", desc->stack_shift);

        if (desc->unk0)
                pandecode_prop("unk0 = 0x%x", desc->unk0);

        if (desc->shared_workgroup_count != 0x1F) {
                pandecode_prop("shared_workgroup_count = %d", desc->shared_workgroup_count);
                if (!is_compute)
                        pandecode_msg("XXX: wrong workgroup count for noncompute\n");
        }

        if (desc->shared_unk1 || desc->shared_shift) {
                pandecode_prop("shared_unk1 = %X", desc->shared_unk1);
                pandecode_prop("shared_shift = %X", desc->shared_shift);

                if (!is_compute)
                        pandecode_msg("XXX: shared memory configured in noncompute shader");
        }

        if (desc->shared_zero) {
                pandecode_msg("XXX: shared memory zero tripped\n");
                pandecode_prop("shared_zero = 0x%" PRIx32, desc->shared_zero);
        }

        if (desc->shared_memory && !is_compute)
                pandecode_msg("XXX: shared memory used in noncompute shader\n");

        MEMORY_PROP(desc, scratchpad);
        MEMORY_PROP(desc, shared_memory);
        MEMORY_PROP(desc, unknown1);

        if (desc->scratchpad) {
                struct pandecode_mapped_memory *smem =
                        pandecode_find_mapped_gpu_mem_containing(desc->scratchpad);

                pandecode_msg("scratchpad size %u\n", smem->length);
        }

}

static struct pandecode_fbd
pandecode_sfbd(uint64_t gpu_va, int job_no, bool is_fragment, unsigned gpu_id)
{
        struct pandecode_mapped_memory *mem = pandecode_find_mapped_gpu_mem_containing(gpu_va);
        const struct mali_single_framebuffer *PANDECODE_PTR_VAR(s, mem, (mali_ptr) gpu_va);

        struct pandecode_fbd info = {
                .has_extra = false,
                .rt_count = 1
        };

        pandecode_log("struct mali_single_framebuffer framebuffer_%"PRIx64"_%d = {\n", gpu_va, job_no);
        pandecode_indent++;

        pandecode_log(".shared_memory = {\n");
        pandecode_indent++;
        pandecode_shared_memory(&s->shared_memory, false);
        pandecode_indent--;
        pandecode_log("},\n");

        pandecode_sfbd_format(s->format);

        info.width = s->width + 1;
        info.height = s->height + 1;

        pandecode_prop("width = MALI_POSITIVE(%" PRId16 ")", info.width);
        pandecode_prop("height = MALI_POSITIVE(%" PRId16 ")", info.height);

        MEMORY_PROP(s, checksum);

        if (s->checksum_stride)
                pandecode_prop("checksum_stride = %d", s->checksum_stride);

        MEMORY_PROP(s, framebuffer);
        pandecode_prop("stride = %d", s->stride);

        /* Earlier in the actual commandstream -- right before width -- but we
         * delay to flow nicer */

        pandecode_log(".clear_flags = ");
        pandecode_log_decoded_flags(clear_flag_info, s->clear_flags);
        pandecode_log_cont(",\n");

        if (s->depth_buffer) {
                MEMORY_PROP(s, depth_buffer);
                pandecode_prop("depth_stride = %d", s->depth_stride);
        }

        if (s->stencil_buffer) {
                MEMORY_PROP(s, stencil_buffer);
                pandecode_prop("stencil_stride = %d", s->stencil_stride);
        }

        if (s->depth_stride_zero ||
            s->stencil_stride_zero ||
            s->zero7 || s->zero8) {
                pandecode_msg("XXX: Depth/stencil zeros tripped\n");
                pandecode_prop("depth_stride_zero = 0x%x",
                               s->depth_stride_zero);
                pandecode_prop("stencil_stride_zero = 0x%x",
                               s->stencil_stride_zero);
                pandecode_prop("zero7 = 0x%" PRIx32,
                               s->zero7);
                pandecode_prop("zero8 = 0x%" PRIx32,
                               s->zero8);
        }

        if (s->clear_color_1 | s->clear_color_2 | s->clear_color_3 | s->clear_color_4) {
                pandecode_prop("clear_color_1 = 0x%" PRIx32, s->clear_color_1);
                pandecode_prop("clear_color_2 = 0x%" PRIx32, s->clear_color_2);
                pandecode_prop("clear_color_3 = 0x%" PRIx32, s->clear_color_3);
                pandecode_prop("clear_color_4 = 0x%" PRIx32, s->clear_color_4);
        }

        if (s->clear_depth_1 != 0 || s->clear_depth_2 != 0 || s->clear_depth_3 != 0 || s->clear_depth_4 != 0) {
                pandecode_prop("clear_depth_1 = %f", s->clear_depth_1);
                pandecode_prop("clear_depth_2 = %f", s->clear_depth_2);
                pandecode_prop("clear_depth_3 = %f", s->clear_depth_3);
                pandecode_prop("clear_depth_4 = %f", s->clear_depth_4);
        }

        if (s->clear_stencil) {
                pandecode_prop("clear_stencil = 0x%x", s->clear_stencil);
        }

        const struct midgard_tiler_descriptor t = s->tiler;

        bool has_hierarchy = !(gpu_id == 0x0720 || gpu_id == 0x0820 || gpu_id == 0x0830);
        pandecode_midgard_tiler_descriptor(&t, s->width + 1, s->height + 1, is_fragment, has_hierarchy);

        pandecode_indent--;
        pandecode_log("};\n");

        pandecode_prop("zero2 = 0x%" PRIx32, s->zero2);
        pandecode_prop("zero4 = 0x%" PRIx32, s->zero4);
        pandecode_prop("zero5 = 0x%" PRIx32, s->zero5);

        pandecode_log_cont(".zero3 = {");

        for (int i = 0; i < sizeof(s->zero3) / sizeof(s->zero3[0]); ++i)
                pandecode_log_cont("%X, ", s->zero3[i]);

        pandecode_log_cont("},\n");

        pandecode_log_cont(".zero6 = {");

        for (int i = 0; i < sizeof(s->zero6) / sizeof(s->zero6[0]); ++i)
                pandecode_log_cont("%X, ", s->zero6[i]);

        pandecode_log_cont("},\n");

        return info;
}

static void
pandecode_compute_fbd(uint64_t gpu_va, int job_no)
{
        struct pandecode_mapped_memory *mem = pandecode_find_mapped_gpu_mem_containing(gpu_va);
        const struct mali_shared_memory *PANDECODE_PTR_VAR(s, mem, (mali_ptr) gpu_va);

        pandecode_log("struct mali_shared_memory shared_%"PRIx64"_%d = {\n", gpu_va, job_no);
        pandecode_indent++;
        pandecode_shared_memory(s, true);
        pandecode_indent--;
        pandecode_log("},\n");
}

/* Extracts the number of components associated with a Mali format */

static unsigned
pandecode_format_component_count(enum mali_format fmt)
{
        /* Mask out the format class */
        unsigned top = fmt & 0b11100000;

        switch (top) {
        case MALI_FORMAT_SNORM:
        case MALI_FORMAT_UINT:
        case MALI_FORMAT_UNORM:
        case MALI_FORMAT_SINT:
                return ((fmt >> 3) & 3) + 1;
        default:
                /* TODO: Validate */
                return 4;
        }
}

/* Extracts a mask of accessed components from a 12-bit Mali swizzle */

static unsigned
pandecode_access_mask_from_channel_swizzle(unsigned swizzle)
{
        unsigned mask = 0;
        assert(MALI_CHANNEL_RED == 0);

        for (unsigned c = 0; c < 4; ++c) {
                enum mali_channel chan = (swizzle >> (3*c)) & 0x7;

                if (chan <= MALI_CHANNEL_ALPHA)
                        mask |= (1 << chan);
        }

        return mask;
}

/* Validates that a (format, swizzle) pair is valid, in the sense that the
 * swizzle doesn't access any components that are undefined in the format.
 * Returns whether the swizzle is trivial (doesn't do any swizzling) and can be
 * omitted */

static bool
pandecode_validate_format_swizzle(enum mali_format fmt, unsigned swizzle)
{
        unsigned nr_comp = pandecode_format_component_count(fmt);
        unsigned access_mask = pandecode_access_mask_from_channel_swizzle(swizzle);
        unsigned valid_mask = (1 << nr_comp) - 1;
        unsigned invalid_mask = ~valid_mask;

        if (access_mask & invalid_mask) {
                pandecode_msg("XXX: invalid components accessed\n");
                return false;
        }

        /* Check for the default non-swizzling swizzle so we can suppress
         * useless printing for the defaults */

        unsigned default_swizzles[4] = {
                MALI_CHANNEL_RED | (MALI_CHANNEL_ZERO  << 3) | (MALI_CHANNEL_ZERO << 6) | (MALI_CHANNEL_ONE   << 9),
                MALI_CHANNEL_RED | (MALI_CHANNEL_GREEN << 3) | (MALI_CHANNEL_ZERO << 6) | (MALI_CHANNEL_ONE   << 9),
                MALI_CHANNEL_RED | (MALI_CHANNEL_GREEN << 3) | (MALI_CHANNEL_BLUE << 6) | (MALI_CHANNEL_ONE   << 9),
                MALI_CHANNEL_RED | (MALI_CHANNEL_GREEN << 3) | (MALI_CHANNEL_BLUE << 6) | (MALI_CHANNEL_ALPHA << 9)
        };

        return (swizzle == default_swizzles[nr_comp - 1]);
}

/* Maps MALI_RGBA32F to rgba32f, etc */

static void
pandecode_format_short(enum mali_format fmt, bool srgb)
{
        /* We want a type-like format, so cut off the initial MALI_ */
        char *format = pandecode_format(fmt);
        format += strlen("MALI_");

        unsigned len = strlen(format);
        char *lower_format = calloc(1, len + 1);

        for (unsigned i = 0; i < len; ++i)
                lower_format[i] = tolower(format[i]);

        /* Sanity check sRGB flag is applied to RGB, per the name */
        if (srgb && lower_format[0] != 'r')
                pandecode_msg("XXX: sRGB applied to non-colour format\n");

        /* Just prefix with an s, so you get formats like srgba8_unorm */
        if (srgb)
                pandecode_log_cont("s");

        pandecode_log_cont("%s", lower_format);
        free(lower_format);
}

static void
pandecode_swizzle(unsigned swizzle, enum mali_format format)
{
        /* First, do some validation */
        bool trivial_swizzle = pandecode_validate_format_swizzle(
                        format, swizzle);

        if (trivial_swizzle)
                return;

        /* Next, print the swizzle */
        pandecode_log_cont(".");

        static const char components[] = "rgba01";

        for (unsigned c = 0; c < 4; ++c) {
                enum mali_channel chan = (swizzle >> (3 * c)) & 0x7;

                if (chan >= MALI_CHANNEL_RESERVED_0) {
                        pandecode_log("XXX: invalid swizzle channel %d\n", chan);
                        continue;
                }
                pandecode_log_cont("%c", components[chan]);
        }
}

static void
pandecode_rt_format(struct mali_rt_format format)
{
        pandecode_log(".format = {\n");
        pandecode_indent++;

        pandecode_prop("unk1 = 0x%" PRIx32, format.unk1);
        pandecode_prop("unk2 = 0x%" PRIx32, format.unk2);
        pandecode_prop("unk3 = 0x%" PRIx32, format.unk3);

        pandecode_prop("block = %s", pandecode_block_format(format.block));

        /* TODO: Map formats so we can check swizzles and print nicely */
        pandecode_log("swizzle");
        pandecode_swizzle(format.swizzle, MALI_RGBA8_UNORM);
        pandecode_log_cont(",\n");

        pandecode_prop("nr_channels = MALI_POSITIVE(%d)",
                       (format.nr_channels + 1));

        pandecode_log(".flags = ");
        pandecode_log_decoded_flags(mfbd_fmt_flag_info, format.flags);
        pandecode_log_cont(",\n");

        /* In theory, the no_preload bit can be cleared to enable MFBD preload,
         * which is a faster hardware-based alternative to the wallpaper method
         * to preserve framebuffer contents across frames. In practice, MFBD
         * preload is buggy on Midgard, and so this is a chicken bit. If this
         * bit isn't set, most likely something broke unrelated to preload */

        if (!format.no_preload) {
                pandecode_msg("XXX: buggy MFBD preload enabled - chicken bit should be clear\n");
                pandecode_prop("no_preload = 0x%" PRIx32, format.no_preload);
        }

        if (format.zero)
                pandecode_prop("zero = 0x%" PRIx32, format.zero);

        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_render_target(uint64_t gpu_va, unsigned job_no, const struct mali_framebuffer *fb)
{
        pandecode_log("struct mali_render_target rts_list_%"PRIx64"_%d[] = {\n", gpu_va, job_no);
        pandecode_indent++;

        for (int i = 0; i < (fb->rt_count_1 + 1); i++) {
                mali_ptr rt_va = gpu_va + i * sizeof(struct mali_render_target);
                struct pandecode_mapped_memory *mem =
                        pandecode_find_mapped_gpu_mem_containing(rt_va);
                const struct mali_render_target *PANDECODE_PTR_VAR(rt, mem, (mali_ptr) rt_va);

                pandecode_log("{\n");
                pandecode_indent++;

                pandecode_rt_format(rt->format);

                if (rt->format.block == MALI_BLOCK_AFBC) {
                        pandecode_log(".afbc = {\n");
                        pandecode_indent++;

                        char *a = pointer_as_memory_reference(rt->afbc.metadata);
                        pandecode_prop("metadata = %s", a);
                        free(a);

                        pandecode_prop("stride = %d", rt->afbc.stride);
                        pandecode_prop("unk = 0x%" PRIx32, rt->afbc.unk);

                        pandecode_indent--;
                        pandecode_log("},\n");
                } else if (rt->afbc.metadata || rt->afbc.stride || rt->afbc.unk) {
                        pandecode_msg("XXX: AFBC disabled but AFBC field set (0x%lX, 0x%x, 0x%x)\n",
                                        rt->afbc.metadata,
                                        rt->afbc.stride,
                                        rt->afbc.unk);
                }

                MEMORY_PROP(rt, framebuffer);
                pandecode_prop("framebuffer_stride = %d", rt->framebuffer_stride);

                if (rt->clear_color_1 | rt->clear_color_2 | rt->clear_color_3 | rt->clear_color_4) {
                        pandecode_prop("clear_color_1 = 0x%" PRIx32, rt->clear_color_1);
                        pandecode_prop("clear_color_2 = 0x%" PRIx32, rt->clear_color_2);
                        pandecode_prop("clear_color_3 = 0x%" PRIx32, rt->clear_color_3);
                        pandecode_prop("clear_color_4 = 0x%" PRIx32, rt->clear_color_4);
                }

                if (rt->zero1 || rt->zero2 || rt->zero3) {
                        pandecode_msg("XXX: render target zeros tripped\n");
                        pandecode_prop("zero1 = 0x%" PRIx64, rt->zero1);
                        pandecode_prop("zero2 = 0x%" PRIx32, rt->zero2);
                        pandecode_prop("zero3 = 0x%" PRIx32, rt->zero3);
                }

                pandecode_indent--;
                pandecode_log("},\n");
        }

        pandecode_indent--;
        pandecode_log("};\n");
}

static struct pandecode_fbd
pandecode_mfbd_bfr(uint64_t gpu_va, int job_no, bool is_fragment, bool is_compute, bool is_bifrost)
{
        struct pandecode_mapped_memory *mem = pandecode_find_mapped_gpu_mem_containing(gpu_va);
        const struct mali_framebuffer *PANDECODE_PTR_VAR(fb, mem, (mali_ptr) gpu_va);

        struct pandecode_fbd info;

        if (is_bifrost && fb->msaa.sample_locations) {
                /* The blob stores all possible sample locations in a single buffer
                 * allocated on startup, and just switches the pointer when switching
                 * MSAA state. For now, we just put the data into the cmdstream, but we
                 * should do something like what the blob does with a real driver.
                 *
                 * There seem to be 32 slots for sample locations, followed by another
                 * 16. The second 16 is just the center location followed by 15 zeros
                 * in all the cases I've identified (maybe shader vs. depth/color
                 * samples?).
                 */

                struct pandecode_mapped_memory *smem = pandecode_find_mapped_gpu_mem_containing(fb->msaa.sample_locations);

                const u16 *PANDECODE_PTR_VAR(samples, smem, fb->msaa.sample_locations);

                pandecode_log("uint16_t sample_locations_%d[] = {\n", job_no);
                pandecode_indent++;

                for (int i = 0; i < 32 + 16; i++) {
                        pandecode_log("%d, %d,\n", samples[2 * i], samples[2 * i + 1]);
                }

                pandecode_indent--;
                pandecode_log("};\n");
        }
 
        pandecode_log("struct mali_framebuffer framebuffer_%"PRIx64"_%d = {\n", gpu_va, job_no);
        pandecode_indent++;

        if (is_bifrost) {
                pandecode_log(".msaa = {\n");
                pandecode_indent++;

                if (fb->msaa.sample_locations)
                        pandecode_prop("sample_locations = sample_locations_%d", job_no);
                else
                        pandecode_msg("XXX: sample_locations missing\n");

                if (fb->msaa.zero1 || fb->msaa.zero2 || fb->msaa.zero4) {
                        pandecode_msg("XXX: multisampling zero tripped\n");
                        pandecode_prop("zero1 = %" PRIx64, fb->msaa.zero1);
                        pandecode_prop("zero2 = %" PRIx64, fb->msaa.zero2);
                        pandecode_prop("zero4 = %" PRIx64, fb->msaa.zero4);
                }

                pandecode_indent--;
                pandecode_log("},\n");
        } else {
                pandecode_log(".shared_memory = {\n");
                pandecode_indent++;
                pandecode_shared_memory(&fb->shared_memory, is_compute);
                pandecode_indent--;
                pandecode_log("},\n");
        }

        info.width = fb->width1 + 1;
        info.height = fb->height1 + 1;
        info.rt_count = fb->rt_count_1 + 1;

        pandecode_prop("width1 = MALI_POSITIVE(%d)", fb->width1 + 1);
        pandecode_prop("height1 = MALI_POSITIVE(%d)", fb->height1 + 1);
        pandecode_prop("width2 = MALI_POSITIVE(%d)", fb->width2 + 1);
        pandecode_prop("height2 = MALI_POSITIVE(%d)", fb->height2 + 1);

        pandecode_prop("unk1 = 0x%x", fb->unk1);
        pandecode_prop("unk2 = 0x%x", fb->unk2);
        pandecode_prop("rt_count_1 = MALI_POSITIVE(%d)", fb->rt_count_1 + 1);
        pandecode_prop("rt_count_2 = %d", fb->rt_count_2);

        pandecode_log(".mfbd_flags = ");
        pandecode_log_decoded_flags(mfbd_flag_info, fb->mfbd_flags);
        pandecode_log_cont(",\n");

        if (fb->clear_stencil)
                pandecode_prop("clear_stencil = 0x%x", fb->clear_stencil);

        if (fb->clear_depth)
                pandecode_prop("clear_depth = %f", fb->clear_depth);

        if (!is_compute)
                if (is_bifrost)
                        pandecode_bifrost_tiler_descriptor(fb);
                else
                        pandecode_midgard_tiler_descriptor(&fb->tiler, fb->width1 + 1, fb->height1 + 1, is_fragment, true);
        else
                pandecode_msg("XXX: skipping compute MFBD, fixme\n");

        if (fb->zero3 || fb->zero4) {
                pandecode_msg("XXX: framebuffer zeros tripped\n");
                pandecode_prop("zero3 = 0x%" PRIx32, fb->zero3);
                pandecode_prop("zero4 = 0x%" PRIx32, fb->zero4);
        }

        pandecode_indent--;
        pandecode_log("};\n");

        gpu_va += sizeof(struct mali_framebuffer);

        info.has_extra = (fb->mfbd_flags & MALI_MFBD_EXTRA) && is_fragment;

        if (info.has_extra) {
                mem = pandecode_find_mapped_gpu_mem_containing(gpu_va);
                const struct mali_framebuffer_extra *PANDECODE_PTR_VAR(fbx, mem, (mali_ptr) gpu_va);

                pandecode_log("struct mali_framebuffer_extra fb_extra_%"PRIx64"_%d = {\n", gpu_va, job_no);
                pandecode_indent++;

                MEMORY_PROP(fbx, checksum);

                if (fbx->checksum_stride)
                        pandecode_prop("checksum_stride = %d", fbx->checksum_stride);

                pandecode_log(".flags_hi = ");
                pandecode_log_decoded_flags(mfbd_extra_flag_hi_info, fbx->flags_lo);
                pandecode_log_cont(",\n");

                pandecode_log(".flags_lo = ");
                pandecode_log_decoded_flags(mfbd_extra_flag_lo_info, fbx->flags_lo);
                pandecode_log_cont(",\n");

                pandecode_prop("zs_block = %s", pandecode_block_format(fbx->zs_block));

                if (fbx->zs_block == MALI_BLOCK_AFBC) {
                        pandecode_log(".ds_afbc = {\n");
                        pandecode_indent++;

                        MEMORY_PROP_DIR(fbx->ds_afbc, depth_stencil_afbc_metadata);
                        pandecode_prop("depth_stencil_afbc_stride = %d",
                                       fbx->ds_afbc.depth_stencil_afbc_stride);
                        MEMORY_PROP_DIR(fbx->ds_afbc, depth_stencil);

                        if (fbx->ds_afbc.zero1 || fbx->ds_afbc.padding) {
                                pandecode_msg("XXX: Depth/stencil AFBC zeros tripped\n");
                                pandecode_prop("zero1 = 0x%" PRIx32,
                                               fbx->ds_afbc.zero1);
                                pandecode_prop("padding = 0x%" PRIx64,
                                               fbx->ds_afbc.padding);
                        }

                        pandecode_indent--;
                        pandecode_log("},\n");
                } else {
                        pandecode_log(".ds_linear = {\n");
                        pandecode_indent++;

                        if (fbx->ds_linear.depth) {
                                MEMORY_PROP_DIR(fbx->ds_linear, depth);
                                pandecode_prop("depth_stride = %d",
                                               fbx->ds_linear.depth_stride);
                        } else if (fbx->ds_linear.depth_stride) {
                                pandecode_msg("XXX: depth stride zero tripped %d\n", fbx->ds_linear.depth_stride);
                        }

                        if (fbx->ds_linear.stencil) {
                                MEMORY_PROP_DIR(fbx->ds_linear, stencil);
                                pandecode_prop("stencil_stride = %d",
                                               fbx->ds_linear.stencil_stride);
                        } else if (fbx->ds_linear.stencil_stride) {
                                pandecode_msg("XXX: stencil stride zero tripped %d\n", fbx->ds_linear.stencil_stride);
                        }

                        if (fbx->ds_linear.depth_stride_zero ||
                            fbx->ds_linear.stencil_stride_zero ||
                            fbx->ds_linear.zero1 || fbx->ds_linear.zero2) {
                                pandecode_msg("XXX: Depth/stencil zeros tripped\n");
                                pandecode_prop("depth_stride_zero = 0x%x",
                                               fbx->ds_linear.depth_stride_zero);
                                pandecode_prop("stencil_stride_zero = 0x%x",
                                               fbx->ds_linear.stencil_stride_zero);
                                pandecode_prop("zero1 = 0x%" PRIx32,
                                               fbx->ds_linear.zero1);
                                pandecode_prop("zero2 = 0x%" PRIx32,
                                               fbx->ds_linear.zero2);
                        }

                        pandecode_indent--;
                        pandecode_log("},\n");
                }

                if (fbx->clear_color_1 | fbx->clear_color_2) {
                        pandecode_prop("clear_color_1 = 0x%" PRIx32, fbx->clear_color_1);
                        pandecode_prop("clear_color_2 = 0x%" PRIx32, fbx->clear_color_2);
                }

                if (fbx->zero3) {
                        pandecode_msg("XXX: fb_extra zeros tripped\n");
                        pandecode_prop("zero3 = 0x%" PRIx64, fbx->zero3);
                }

                pandecode_indent--;
                pandecode_log("};\n");

                gpu_va += sizeof(struct mali_framebuffer_extra);
        }

        if (is_fragment)
                pandecode_render_target(gpu_va, job_no, fb);

        return info;
}

/* Just add a comment decoding the shift/odd fields forming the padded vertices
 * count */

static void
pandecode_padded_vertices(unsigned shift, unsigned k)
{
        unsigned odd = 2*k + 1;
        unsigned pot = 1 << shift;
        pandecode_msg("padded_num_vertices = %d\n", odd * pot);
}

/* Given a magic divisor, recover what we were trying to divide by.
 *
 * Let m represent the magic divisor. By definition, m is an element on Z, whre
 * 0 <= m < 2^N, for N bits in m.
 *
 * Let q represent the number we would like to divide by.
 *
 * By definition of a magic divisor for N-bit unsigned integers (a number you
 * multiply by to magically get division), m is a number such that:
 *
 *      (m * x) & (2^N - 1) = floor(x/q).
 *      for all x on Z where 0 <= x < 2^N
 *
 * Ignore the case where any of the above values equals zero; it is irrelevant
 * for our purposes (instanced arrays).
 *
 * Choose x = q. Then:
 *
 *      (m * x) & (2^N - 1) = floor(x/q).
 *      (m * q) & (2^N - 1) = floor(q/q).
 *
 *      floor(q/q) = floor(1) = 1, therefore:
 *
 *      (m * q) & (2^N - 1) = 1
 *
 * Recall the identity that the bitwise AND of one less than a power-of-two
 * equals the modulo with that power of two, i.e. for all x:
 *
 *      x & (2^N - 1) = x % N
 *
 * Therefore:
 *
 *      mq % (2^N) = 1
 *
 * By definition, a modular multiplicative inverse of a number m is the number
 * q such that with respect to a modulos M:
 *
 *      mq % M = 1
 *
 * Therefore, q is the modular multiplicative inverse of m with modulus 2^N.
 *
 */

static void
pandecode_magic_divisor(uint32_t magic, unsigned shift, unsigned orig_divisor, unsigned extra)
{
#if 0
        /* Compute the modular inverse of `magic` with respect to 2^(32 -
         * shift) the most lame way possible... just repeatedly add.
         * Asymptoptically slow but nobody cares in practice, unless you have
         * massive numbers of vertices or high divisors. */

        unsigned inverse = 0;

        /* Magic implicitly has the highest bit set */
        magic |= (1 << 31);

        /* Depending on rounding direction */
        if (extra)
                magic++;

        for (;;) {
                uint32_t product = magic * inverse;

                if (shift) {
                        product >>= shift;
                }

                if (product == 1)
                        break;

                ++inverse;
        }

        pandecode_msg("dividing by %d (maybe off by two)\n", inverse);

        /* Recall we're supposed to divide by (gl_level_divisor *
         * padded_num_vertices) */

        unsigned padded_num_vertices = inverse / orig_divisor;

        pandecode_msg("padded_num_vertices = %d\n", padded_num_vertices);
#endif
}

static void
pandecode_attributes(const struct pandecode_mapped_memory *mem,
                            mali_ptr addr, int job_no, char *suffix,
                            int count, bool varying, enum mali_job_type job_type)
{
        char *prefix = varying ? "varying" : "attribute";
        assert(addr);

        if (!count) {
                pandecode_msg("warn: No %s records\n", prefix);
                return;
        }

        union mali_attr *attr = pandecode_fetch_gpu_mem(mem, addr, sizeof(union mali_attr) * count);

        for (int i = 0; i < count; ++i) {
                /* First, check for special records */
                if (attr[i].elements < MALI_RECORD_SPECIAL) {
                        if (attr[i].size)
                                pandecode_msg("XXX: tripped size=%d\n", attr[i].size);

                        if (attr[i].stride) {
                                /* gl_InstanceID passes a magic divisor in the
                                 * stride field to divide by the padded vertex
                                 * count. No other records should do so, so
                                 * stride should otherwise be zero. Note that
                                 * stride in the usual attribute sense doesn't
                                 * apply to special records. */

                                bool has_divisor = attr[i].elements == MALI_ATTR_INSTANCEID;

                                pandecode_log_cont("/* %smagic divisor = %X */ ",
                                                has_divisor ? "" : "XXX: ", attr[i].stride);
                        }

                        if (attr[i].shift || attr[i].extra_flags) {
                                /* Attributes use these fields for
                                 * instancing/padding/etc type issues, but
                                 * varyings don't */

                                pandecode_log_cont("/* %sshift=%d, extra=%d */ ",
                                                varying ? "XXX: " : "",
                                                attr[i].shift, attr[i].extra_flags);
                        }

                        /* Print the special record name */
                        bool attribute = false;
                        pandecode_log("%s_%d = %s;\n", prefix, i, pandecode_special_record(attr[i].elements, &attribute));

                        /* Sanity check */
                        if (attribute == varying)
                                pandecode_msg("XXX: mismatched special record\n");

                        continue;
        }

                enum mali_attr_mode mode = attr[i].elements & 7;

                if (mode == MALI_ATTR_UNUSED)
                        pandecode_msg("XXX: unused attribute record\n");

                /* For non-linear records, we need to print the type of record */
                if (mode != MALI_ATTR_LINEAR)
                        pandecode_log_cont("%s ", pandecode_attr_mode_short(mode));

                /* Print the name to link with attr_meta */
                pandecode_log_cont("%s_%d", prefix, i);

                /* Print the stride and size */
                pandecode_log_cont("<%u>[%u]", attr[i].stride, attr[i].size);

                /* TODO: Sanity check the quotient itself. It must be equal to
                 * (or be greater than, if the driver added padding) the padded
                 * vertex count. */

                /* Finally, print the pointer */
                mali_ptr raw_elements = attr[i].elements & ~7;
                char *a = pointer_as_memory_reference(raw_elements);
                pandecode_log_cont(" = (%s);\n", a);
                free(a);

                /* Check the pointer */
                pandecode_validate_buffer(raw_elements, attr[i].size);

                /* shift/extra_flags exist only for instanced */
                if (attr[i].shift | attr[i].extra_flags) {
                        /* These are set to random values by the blob for
                         * varyings, most likely a symptom of uninitialized
                         * memory where the hardware masked the bug. As such we
                         * put this at a warning, not an error. */

                        if (mode == MALI_ATTR_LINEAR)
                                pandecode_msg("warn: instancing fields set for linear\n");

                        pandecode_prop("shift = %d", attr[i].shift);
                        pandecode_prop("extra_flags = %d", attr[i].extra_flags);
                }

                /* Decode further where possible */

                if (mode == MALI_ATTR_MODULO) {
                        pandecode_padded_vertices(
                                attr[i].shift,
                                attr[i].extra_flags);
                }

                if (mode == MALI_ATTR_NPOT_DIVIDE) {
                        i++;
                        pandecode_log("{\n");
                        pandecode_indent++;
                        pandecode_prop("unk = 0x%x", attr[i].unk);
                        pandecode_prop("magic_divisor = 0x%08x", attr[i].magic_divisor);
                        if (attr[i].zero != 0)
                                pandecode_prop("XXX: zero tripped (0x%x)\n", attr[i].zero);
                        pandecode_prop("divisor = %d", attr[i].divisor);
                        pandecode_magic_divisor(attr[i].magic_divisor, attr[i - 1].shift, attr[i].divisor, attr[i - 1].extra_flags);
                        pandecode_indent--;
                        pandecode_log("}, \n");
                }

        }

        pandecode_log("\n");
}

static mali_ptr
pandecode_shader_address(const char *name, mali_ptr ptr)
{
        /* TODO: Decode flags */
        mali_ptr shader_ptr = ptr & ~15;

        char *a = pointer_as_memory_reference(shader_ptr);
        pandecode_prop("%s = (%s) | %d", name, a, (int) (ptr & 15));
        free(a);

        return shader_ptr;
}

static void
pandecode_stencil(const char *name, const struct mali_stencil_test *stencil)
{
        unsigned any_nonzero =
                stencil->ref | stencil->mask | stencil->func |
                stencil->sfail | stencil->dpfail | stencil->dppass;

        if (any_nonzero == 0)
                return;

        const char *func = pandecode_func(stencil->func);
        const char *sfail = pandecode_stencil_op(stencil->sfail);
        const char *dpfail = pandecode_stencil_op(stencil->dpfail);
        const char *dppass = pandecode_stencil_op(stencil->dppass);

        if (stencil->zero)
                pandecode_msg("XXX: stencil zero tripped: %X\n", stencil->zero);

        pandecode_log(".stencil_%s = {\n", name);
        pandecode_indent++;
        pandecode_prop("ref = %d", stencil->ref);
        pandecode_prop("mask = 0x%02X", stencil->mask);
        pandecode_prop("func = %s", func);
        pandecode_prop("sfail = %s", sfail);
        pandecode_prop("dpfail = %s", dpfail);
        pandecode_prop("dppass = %s", dppass);
        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_blend_equation(const struct mali_blend_equation *blend)
{
        if (blend->zero1)
                pandecode_msg("XXX: blend zero tripped: %X\n", blend->zero1);

        pandecode_log(".equation = {\n");
        pandecode_indent++;

        pandecode_prop("rgb_mode = 0x%X", blend->rgb_mode);
        pandecode_prop("alpha_mode = 0x%X", blend->alpha_mode);

        pandecode_log(".color_mask = ");
        pandecode_log_decoded_flags(mask_flag_info, blend->color_mask);
        pandecode_log_cont(",\n");

        pandecode_indent--;
        pandecode_log("},\n");
}

/* Decodes a Bifrost blend constant. See the notes in bifrost_blend_rt */

static unsigned
decode_bifrost_constant(u16 constant)
{
        float lo = (float) (constant & 0xFF);
        float hi = (float) (constant >> 8);

        return (hi / 255.0) + (lo / 65535.0);
}

static mali_ptr
pandecode_bifrost_blend(void *descs, int job_no, int rt_no)
{
        struct bifrost_blend_rt *b =
                ((struct bifrost_blend_rt *) descs) + rt_no;

        pandecode_log("struct bifrost_blend_rt blend_rt_%d_%d = {\n", job_no, rt_no);
        pandecode_indent++;

        pandecode_prop("flags = 0x%" PRIx16, b->flags);
        pandecode_prop("constant = 0x%" PRIx8 " /* %f */",
                       b->constant, decode_bifrost_constant(b->constant));

        /* TODO figure out blend shader enable bit */
        pandecode_blend_equation(&b->equation);
        pandecode_prop("unk2 = 0x%" PRIx16, b->unk2);
        pandecode_prop("index = 0x%" PRIx16, b->index);
        pandecode_prop("shader = 0x%" PRIx32, b->shader);

        pandecode_indent--;
        pandecode_log("},\n");

        return 0;
}

static mali_ptr
pandecode_midgard_blend(union midgard_blend *blend, bool is_shader)
{
        /* constant/equation is in a union */
        if (!blend->shader)
                return 0;

        pandecode_log(".blend = {\n");
        pandecode_indent++;

        if (is_shader) {
                pandecode_shader_address("shader", blend->shader);
        } else {
                pandecode_blend_equation(&blend->equation);
                pandecode_prop("constant = %f", blend->constant);
        }

        pandecode_indent--;
        pandecode_log("},\n");

        /* Return blend shader to disassemble if present */
        return is_shader ? (blend->shader & ~0xF) : 0;
}

static mali_ptr
pandecode_midgard_blend_mrt(void *descs, int job_no, int rt_no)
{
        struct midgard_blend_rt *b =
                ((struct midgard_blend_rt *) descs) + rt_no;

        /* Flags determine presence of blend shader */
        bool is_shader = (b->flags & 0xF) >= 0x2;

        pandecode_log("struct midgard_blend_rt blend_rt_%d_%d = {\n", job_no, rt_no);
        pandecode_indent++;

        pandecode_prop("flags = 0x%" PRIx64, b->flags);

        union midgard_blend blend = b->blend;
        mali_ptr shader = pandecode_midgard_blend(&blend, is_shader);

        pandecode_indent--;
        pandecode_log("};\n");

        return shader;
}

/* Attributes and varyings have descriptor records, which contain information
 * about their format and ordering with the attribute/varying buffers. We'll
 * want to validate that the combinations specified are self-consistent.
 */

static int
pandecode_attribute_meta(int job_no, int count, const struct mali_vertex_tiler_postfix *v, bool varying, char *suffix)
{
        char base[128];
        char *prefix = varying ? "varying" : "attribute";
        unsigned max_index = 0;
        snprintf(base, sizeof(base), "%s_meta", prefix);

        struct mali_attr_meta *attr_meta;
        mali_ptr p = varying ? v->varying_meta : v->attribute_meta;

        struct pandecode_mapped_memory *attr_mem = pandecode_find_mapped_gpu_mem_containing(p);

        for (int i = 0; i < count; ++i, p += sizeof(struct mali_attr_meta)) {
                attr_meta = pandecode_fetch_gpu_mem(attr_mem, p,
                                                    sizeof(*attr_mem));

                /* If the record is discard, it should be zero for everything else */

                if (attr_meta->format == MALI_VARYING_DISCARD) {
                        uint64_t zero =
                                attr_meta->index |
                                attr_meta->unknown1 |
                                attr_meta->unknown3 |
                                attr_meta->src_offset;

                        if (zero)
                                pandecode_msg("XXX: expected empty record for varying discard\n");

                        /* We want to look for a literal 0000 swizzle -- this
                         * is not encoded with all zeroes, however */

                        enum mali_channel z = MALI_CHANNEL_ZERO;
                        unsigned zero_swizzle = z | (z << 3) | (z << 6) | (z << 9);
                        bool good_swizzle = attr_meta->swizzle == zero_swizzle;

                        if (!good_swizzle)
                                pandecode_msg("XXX: expected zero swizzle for discard\n");

                        if (!varying)
                                pandecode_msg("XXX: cannot discard attribute\n");

                        /* If we're all good, omit the record */
                        if (!zero && varying && good_swizzle) {
                                pandecode_log("/* discarded varying */\n");
                                continue;
                        }
                }

                if (attr_meta->index > max_index)
                        max_index = attr_meta->index;

                if (attr_meta->unknown1 != 0x2) {
                        pandecode_msg("XXX: expected unknown1 = 0x2\n");
                        pandecode_prop("unknown1 = 0x%" PRIx64, (u64) attr_meta->unknown1);
                }

                if (attr_meta->unknown3) {
                        pandecode_msg("XXX: unexpected unknown3 set\n");
                        pandecode_prop("unknown3 = 0x%" PRIx64, (u64) attr_meta->unknown3);
                }

                pandecode_format_short(attr_meta->format, false);
                pandecode_log_cont(" %s_%u", prefix, attr_meta->index);

                if (attr_meta->src_offset)
                        pandecode_log_cont("[%u]", attr_meta->src_offset);

                pandecode_swizzle(attr_meta->swizzle, attr_meta->format);

                pandecode_log_cont(";\n");
        }

        pandecode_log("\n");

        return count ? (max_index + 1) : 0;
}

/* return bits [lo, hi) of word */
static u32
bits(u32 word, u32 lo, u32 hi)
{
        if (hi - lo >= 32)
                return word; // avoid undefined behavior with the shift

        return (word >> lo) & ((1 << (hi - lo)) - 1);
}

static void
pandecode_vertex_tiler_prefix(struct mali_vertex_tiler_prefix *p, int job_no, bool graphics)
{
        pandecode_log(".prefix = {\n");
        pandecode_indent++;

        /* Decode invocation_count. See the comment before the definition of
         * invocation_count for an explanation.
         */

        unsigned size_y_shift = bits(p->invocation_shifts, 0, 5);
        unsigned size_z_shift = bits(p->invocation_shifts, 5, 10);
        unsigned workgroups_x_shift = bits(p->invocation_shifts, 10, 16);
        unsigned workgroups_y_shift = bits(p->invocation_shifts, 16, 22);
        unsigned workgroups_z_shift = bits(p->invocation_shifts, 22, 28);
        unsigned workgroups_x_shift_2 = bits(p->invocation_shifts, 28, 32);

        unsigned size_x = bits(p->invocation_count, 0, size_y_shift) + 1;
        unsigned size_y = bits(p->invocation_count, size_y_shift, size_z_shift) + 1;
        unsigned size_z = bits(p->invocation_count, size_z_shift, workgroups_x_shift) + 1;

        unsigned groups_x = bits(p->invocation_count, workgroups_x_shift, workgroups_y_shift) + 1;
        unsigned groups_y = bits(p->invocation_count, workgroups_y_shift, workgroups_z_shift) + 1;
        unsigned groups_z = bits(p->invocation_count, workgroups_z_shift, 32) + 1;

        /* Even though we have this decoded, we want to ensure that the
         * representation is "unique" so we don't lose anything by printing only
         * the final result. More specifically, we need to check that we were
         * passed something in canonical form, since the definition per the
         * hardware is inherently not unique. How? Well, take the resulting
         * decode and pack it ourselves! If it is bit exact with what we
         * decoded, we're good to go. */

        struct mali_vertex_tiler_prefix ref;
        panfrost_pack_work_groups_compute(&ref, groups_x, groups_y, groups_z, size_x, size_y, size_z, graphics);

        bool canonical =
                (p->invocation_count == ref.invocation_count) &&
                (p->invocation_shifts == ref.invocation_shifts);

        if (!canonical) {
                pandecode_msg("XXX: non-canonical workgroups packing\n");
                pandecode_msg("expected: %X, %X",
                                ref.invocation_count,
                                ref.invocation_shifts);

                pandecode_prop("invocation_count = 0x%" PRIx32, p->invocation_count);
                pandecode_prop("size_y_shift = %d", size_y_shift);
                pandecode_prop("size_z_shift = %d", size_z_shift);
                pandecode_prop("workgroups_x_shift = %d", workgroups_x_shift);
                pandecode_prop("workgroups_y_shift = %d", workgroups_y_shift);
                pandecode_prop("workgroups_z_shift = %d", workgroups_z_shift);
                pandecode_prop("workgroups_x_shift_2 = %d", workgroups_x_shift_2);
        }

        /* Regardless, print the decode */
        pandecode_msg("size (%d, %d, %d), count (%d, %d, %d)\n",
                        size_x, size_y, size_z,
                        groups_x, groups_y, groups_z);

        /* TODO: Decode */
        if (p->unknown_draw)
                pandecode_prop("unknown_draw = 0x%" PRIx32, p->unknown_draw);

        pandecode_prop("workgroups_x_shift_3 = 0x%" PRIx32, p->workgroups_x_shift_3);

        if (p->draw_mode != MALI_DRAW_NONE)
                pandecode_prop("draw_mode = %s", pandecode_draw_mode(p->draw_mode));

        /* Index count only exists for tiler jobs anyway */

        if (p->index_count)
                pandecode_prop("index_count = MALI_POSITIVE(%" PRId32 ")", p->index_count + 1);


        unsigned index_raw_size = (p->unknown_draw & MALI_DRAW_INDEXED_SIZE);
        index_raw_size >>= MALI_DRAW_INDEXED_SHIFT;

        /* Validate an index buffer is present if we need one. TODO: verify
         * relationship between invocation_count and index_count */

        if (p->indices) {
                unsigned count = p->index_count;

                /* Grab the size */
                unsigned size = (index_raw_size == 0x3) ? 4 : index_raw_size;

                /* Ensure we got a size, and if so, validate the index buffer
                 * is large enough to hold a full set of indices of the given
                 * size */

                if (!index_raw_size)
                        pandecode_msg("XXX: index size missing\n");
                else
                        pandecode_validate_buffer(p->indices, count * size);
        } else if (index_raw_size)
                pandecode_msg("XXX: unexpected index size %u\n", index_raw_size);

        if (p->offset_bias_correction)
                pandecode_prop("offset_bias_correction = %d", p->offset_bias_correction);

        /* TODO: Figure out what this is. It's not zero */
        pandecode_prop("zero1 = 0x%" PRIx32, p->zero1);

        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_uniform_buffers(mali_ptr pubufs, int ubufs_count, int job_no)
{
        struct pandecode_mapped_memory *umem = pandecode_find_mapped_gpu_mem_containing(pubufs);
        uint64_t *PANDECODE_PTR_VAR(ubufs, umem, pubufs);

        for (int i = 0; i < ubufs_count; i++) {
                unsigned size = (ubufs[i] & ((1 << 10) - 1)) * 16;
                mali_ptr addr = (ubufs[i] >> 10) << 2;

                pandecode_validate_buffer(addr, size);

                char *ptr = pointer_as_memory_reference(addr);
                pandecode_log("ubuf_%d[%u] = %s;\n", i, size, ptr);
                free(ptr);
        }

        pandecode_log("\n");
}

static void
pandecode_uniforms(mali_ptr uniforms, unsigned uniform_count)
{
        pandecode_validate_buffer(uniforms, uniform_count * 16);

        char *ptr = pointer_as_memory_reference(uniforms);
        pandecode_log("vec4 uniforms[%u] = %s;\n", uniform_count, ptr);
        free(ptr);
}

static const char *
shader_type_for_job(unsigned type)
{
        switch (type) {
        case JOB_TYPE_VERTEX:  return "VERTEX";
        case JOB_TYPE_TILER:   return "FRAGMENT";
        case JOB_TYPE_COMPUTE: return "COMPUTE";
        default:
                               return "UNKNOWN";
        }
}

static unsigned shader_id = 0;

static struct midgard_disasm_stats
pandecode_shader_disassemble(mali_ptr shader_ptr, int shader_no, int type,
                             bool is_bifrost, unsigned gpu_id)
{
        struct pandecode_mapped_memory *mem = pandecode_find_mapped_gpu_mem_containing(shader_ptr);
        uint8_t *PANDECODE_PTR_VAR(code, mem, shader_ptr);

        /* Compute maximum possible size */
        size_t sz = mem->length - (shader_ptr - mem->gpu_va);

        /* Print some boilerplate to clearly denote the assembly (which doesn't
         * obey indentation rules), and actually do the disassembly! */

        pandecode_log_cont("\n\n");

        struct midgard_disasm_stats stats;

        if (is_bifrost) {
                disassemble_bifrost(pandecode_dump_stream, code, sz, true);

                /* TODO: Extend stats to Bifrost */
                stats.texture_count = -128;
                stats.sampler_count = -128;
                stats.attribute_count = -128;
                stats.varying_count = -128;
                stats.uniform_count = -128;
                stats.uniform_buffer_count = -128;
                stats.work_count = -128;

                stats.instruction_count = 0;
                stats.bundle_count = 0;
                stats.quadword_count = 0;
                stats.helper_invocations = false;
        } else {
                stats = disassemble_midgard(pandecode_dump_stream,
                                code, sz, gpu_id,
                                type == JOB_TYPE_TILER ?
                                MESA_SHADER_FRAGMENT : MESA_SHADER_VERTEX);
        }

        /* Print shader-db stats. Skip COMPUTE jobs since they are used for
         * driver-internal purposes with the blob and interfere */

        bool should_shaderdb = type != JOB_TYPE_COMPUTE;

        if (should_shaderdb) {
                unsigned nr_threads =
                        (stats.work_count <= 4) ? 4 :
                        (stats.work_count <= 8) ? 2 :
                        1;

                pandecode_log_cont("shader%d - MESA_SHADER_%s shader: "
                        "%u inst, %u bundles, %u quadwords, "
                        "%u registers, %u threads, 0 loops, 0:0 spills:fills\n\n\n",
                        shader_id++,
                        shader_type_for_job(type),
                        stats.instruction_count, stats.bundle_count, stats.quadword_count,
                        stats.work_count, nr_threads);
        }


        return stats;
}

static void
pandecode_texture_payload(mali_ptr payload,
                          enum mali_texture_type type,
                          enum mali_texture_layout layout,
                          bool manual_stride,
                          uint8_t levels,
                          uint16_t depth,
                          uint16_t array_size,
                          struct pandecode_mapped_memory *tmem)
{
        pandecode_log(".payload = {\n");
        pandecode_indent++;

        /* A bunch of bitmap pointers follow.
         * We work out the correct number,
         * based on the mipmap/cubemap
         * properties, but dump extra
         * possibilities to futureproof */

        int bitmap_count = levels + 1;

        /* Miptree for each face */
        if (type == MALI_TEX_CUBE)
                bitmap_count *= 6;
        else if (type == MALI_TEX_3D && layout == MALI_TEXTURE_LINEAR)
                bitmap_count *= (depth + 1);

        /* Array of textures */
        bitmap_count *= (array_size + 1);

        /* Stride for each element */
        if (manual_stride)
                bitmap_count *= 2;

        mali_ptr *pointers_and_strides = pandecode_fetch_gpu_mem(tmem,
                payload, sizeof(mali_ptr) * bitmap_count);
        for (int i = 0; i < bitmap_count; ++i) {
                /* How we dump depends if this is a stride or a pointer */

                if (manual_stride && (i & 1)) {
                        /* signed 32-bit snuck in as a 64-bit pointer */
                        uint64_t stride_set = pointers_and_strides[i];
                        uint32_t clamped_stride = stride_set;
                        int32_t stride = clamped_stride;
                        assert(stride_set == clamped_stride);
                        pandecode_log("(mali_ptr) %d /* stride */, \n", stride);
                } else {
                        char *a = pointer_as_memory_reference(pointers_and_strides[i]);
                        pandecode_log("%s, \n", a);
                        free(a);
                }
        }

        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_texture(mali_ptr u,
                struct pandecode_mapped_memory *tmem,
                unsigned job_no, unsigned tex)
{
        struct mali_texture_descriptor *PANDECODE_PTR_VAR(t, tmem, u);

        pandecode_log("struct mali_texture_descriptor texture_descriptor_%"PRIx64"_%d_%d = {\n", u, job_no, tex);
        pandecode_indent++;

        pandecode_prop("width = %" PRId32, t->width);
        pandecode_prop("height = %" PRId32, t->height);
        pandecode_prop("depth = %" PRId32, t->depth);
        pandecode_prop("array_size = %" PRId32, t->array_size);

        pandecode_log("\n");
        pandecode_prop("f.swizzle = 0x%" PRIx32, t->format.swizzle);
        pandecode_prop("f.format = 0x%" PRIx32, t->format.format);
        pandecode_prop("f.srgb = 0x%" PRIx32, t->format.srgb);
        pandecode_prop("f.unknown1 = 0x%" PRIx32, t->format.unknown1);
        pandecode_prop("f.type = %" PRId32, t->format.type);
        pandecode_prop("f.layout = %" PRId32, t->format.layout);
        pandecode_prop("f.unknown2 = 0x%" PRIx32, t->format.unknown2);
        pandecode_prop("f.manual_stride = %" PRId32, t->format.manual_stride);
        pandecode_prop("f.zero = 0x%" PRIx32, t->format.zero);
        pandecode_log("\n");

        pandecode_prop("unknown3 = 0x%" PRIx32, t->unknown3);
        pandecode_prop("unknown3A = 0x%" PRIx32, t->unknown3A);
        pandecode_prop("levels = %" PRId32, t->levels);
        pandecode_prop("swizzle = 0x%" PRIx32, t->swizzle);
        pandecode_prop("swizzle_zero = 0x%" PRIx32, t->swizzle_zero);

        pandecode_prop("unknown5 = 0x%" PRIx32, t->unknown5);
        pandecode_prop("unknown6 = 0x%" PRIx32, t->unknown6);
        pandecode_prop("unknown7 = 0x%" PRIx32, t->unknown7);
        pandecode_log("\n");

        struct mali_texture_format f = t->format;

        /* See the definiton of enum mali_texture_type */

        bool is_cube = f.type == MALI_TEX_CUBE;
        unsigned dimension = is_cube ? 2 : f.type;

        pandecode_make_indent();

        /* Print the layout. Default is linear; a modifier can denote AFBC or
         * u-interleaved/tiled modes */

        if (f.layout == MALI_TEXTURE_AFBC)
                pandecode_log_cont("afbc");
        else if (f.layout == MALI_TEXTURE_TILED)
                pandecode_log_cont("tiled");
        else if (f.layout == MALI_TEXTURE_LINEAR)
                pandecode_log_cont("linear");
        else
                pandecode_msg("XXX: invalid texture layout 0x%X\n", f.layout);

        pandecode_swizzle(t->swizzle, f.format);
        pandecode_log_cont(" ");

        /* Distinguish cube/2D with modifier */

        if (is_cube)
                pandecode_log_cont("cube ");

        pandecode_format_short(f.format, f.srgb);
        pandecode_swizzle(f.swizzle, f.format);

        /* All four width/height/depth/array_size dimensions are present
         * regardless of the type of texture, but it is an error to have
         * non-zero dimensions for unused dimensions. Verify this. array_size
         * can always be set, as can width. */

        if (t->height && dimension < 2)
                pandecode_msg("XXX: nonzero height for <2D texture\n");

        if (t->depth && dimension < 3)
                pandecode_msg("XXX: nonzero depth for <2D texture\n");

        /* Print only the dimensions that are actually there */

        pandecode_log_cont(": %d", t->width + 1);

        if (dimension >= 2)
                pandecode_log_cont("x%u", t->height + 1);

        if (dimension >= 3)
                pandecode_log_cont("x%u", t->depth + 1);

        if (t->array_size)
                pandecode_log_cont("[%u]", t->array_size + 1);

        if (t->levels)
                pandecode_log_cont(" mip %u", t->levels);

        pandecode_log_cont("\n");

        if (f.unknown1 | f.zero) {
                pandecode_msg("XXX: texture format zero tripped\n");
                pandecode_prop("unknown1 = %" PRId32, f.unknown1);
                pandecode_prop("zero = %" PRId32, f.zero);
        }

        if (!f.unknown2) {
                pandecode_msg("XXX: expected unknown texture bit set\n");
                pandecode_prop("unknown2 = %" PRId32, f.unknown2);
        }

        if (t->swizzle_zero) {
                pandecode_msg("XXX: swizzle zero tripped\n");
                pandecode_prop("swizzle_zero = %d", t->swizzle_zero);
        }

        if (t->unknown3 | t->unknown3A | t->unknown5 | t->unknown6 | t->unknown7) {
                pandecode_msg("XXX: texture zero tripped\n");
                pandecode_prop("unknown3 = %" PRId16, t->unknown3);
                pandecode_prop("unknown3A = %" PRId8, t->unknown3A);
                pandecode_prop("unknown5 = 0x%" PRIx32, t->unknown5);
                pandecode_prop("unknown6 = 0x%" PRIx32, t->unknown6);
                pandecode_prop("unknown7 = 0x%" PRIx32, t->unknown7);
        }

        pandecode_texture_payload(u + sizeof(*t), f.type, f.layout, f.manual_stride, t->levels, t->depth, t->array_size, tmem);

        pandecode_indent--;
        pandecode_log("};\n");
}

static void
pandecode_bifrost_texture(
                const struct bifrost_texture_descriptor *t,
                unsigned job_no,
                unsigned tex)
{
        pandecode_log("struct bifrost_texture_descriptor texture_descriptor_%d_%d = {\n", job_no, tex);
        pandecode_indent++;

        pandecode_prop("format_unk = 0x%" PRIx32, t->format_unk);
        pandecode_prop("type = %" PRId32, t->type);
        pandecode_prop("format_unk2 = 0x%" PRIx32, t->format_unk2);
        pandecode_prop("format = 0x%" PRIx32, t->format);
        pandecode_prop("srgb = 0x%" PRIx32, t->srgb);
        pandecode_prop("format_unk3 = 0x%" PRIx32, t->format_unk3);
        pandecode_prop("width = %" PRId32, t->width);
        pandecode_prop("height = %" PRId32, t->height);
        pandecode_prop("swizzle = 0x%" PRIx32, t->swizzle);
        pandecode_prop("levels = %" PRId32, t->levels);
        pandecode_prop("unk1 = 0x%" PRIx32, t->unk1);
        pandecode_prop("levels_unk = %" PRId32, t->levels_unk);
        pandecode_prop("level_2 = %" PRId32, t->level_2);
        pandecode_prop("payload = 0x%" PRIx64, t->payload);
        pandecode_prop("array_size = %" PRId32, t->array_size);
        pandecode_prop("unk4 = 0x%" PRIx32, t->unk4);
        pandecode_prop("depth = %" PRId32, t->depth);
        pandecode_prop("unk5 = 0x%" PRIx32, t->unk5);
        pandecode_log("\n");

        /* See the definiton of enum mali_texture_type */

        bool is_cube = t->type == MALI_TEX_CUBE;
        unsigned dimension = is_cube ? 2 : t->type;

        /* Print the layout. Default is linear; a modifier can denote AFBC or
         * u-interleaved/tiled modes */

        if (t->layout == MALI_TEXTURE_AFBC)
                pandecode_log_cont("afbc");
        else if (t->layout == MALI_TEXTURE_TILED)
                pandecode_log_cont("tiled");
        else if (t->layout == MALI_TEXTURE_LINEAR)
                pandecode_log_cont("linear");
        else
                pandecode_msg("XXX: invalid texture layout 0x%X\n", t->layout);

        pandecode_swizzle(t->swizzle, t->format);
        pandecode_log_cont(" ");

        /* Distinguish cube/2D with modifier */

        if (is_cube)
                pandecode_log_cont("cube ");

        pandecode_format_short(t->format, t->srgb);

        /* All four width/height/depth/array_size dimensions are present
         * regardless of the type of texture, but it is an error to have
         * non-zero dimensions for unused dimensions. Verify this. array_size
         * can always be set, as can width. */

        if (t->height && dimension < 2)
                pandecode_msg("XXX: nonzero height for <2D texture\n");

        if (t->depth && dimension < 3)
                pandecode_msg("XXX: nonzero depth for <2D texture\n");

        /* Print only the dimensions that are actually there */

        pandecode_log_cont(": %d", t->width + 1);

        if (dimension >= 2)
                pandecode_log_cont("x%u", t->height + 1);

        if (dimension >= 3)
                pandecode_log_cont("x%u", t->depth + 1);

        if (t->array_size)
                pandecode_log_cont("[%u]", t->array_size + 1);

        if (t->levels)
                pandecode_log_cont(" mip %u", t->levels);

        pandecode_log_cont("\n");

        struct pandecode_mapped_memory *tmem = pandecode_find_mapped_gpu_mem_containing(t->payload);
        pandecode_texture_payload(t->payload, t->type, t->layout,
                                  true, t->levels, t->depth,
                                  t->array_size, tmem);

        pandecode_indent--;
        pandecode_log("};\n");
}

/* For shader properties like texture_count, we have a claimed property in the shader_meta, and the actual Truth from static analysis (this may just be an upper limit). We validate accordingly */

static void
pandecode_shader_prop(const char *name, unsigned claim, signed truth, bool fuzzy)
{
        /* Nothing to do */
        if (claim == truth)
                return;

        if (fuzzy && (truth < 0))
                pandecode_msg("XXX: fuzzy %s, claimed %d, expected %d\n", name, claim, truth);

        if ((truth >= 0) && !fuzzy) {
                pandecode_msg("%s: expected %s = %d, claimed %u\n",
                                (truth < claim) ? "warn" : "XXX",
                                name, truth, claim);
        } else if ((claim > -truth) && !fuzzy) {
                pandecode_msg("XXX: expected %s <= %u, claimed %u\n",
                                name, -truth, claim);
        } else if (fuzzy && (claim < truth))
                pandecode_msg("XXX: expected %s >= %u, claimed %u\n",
                                name, truth, claim);

        pandecode_log(".%s = %" PRId16, name, claim);

        if (fuzzy)
                pandecode_log_cont(" /* %u used */", truth);

        pandecode_log_cont(",\n");
}

static void
pandecode_blend_shader_disassemble(mali_ptr shader, int job_no, int job_type,
                                   bool is_bifrost, unsigned gpu_id)
{
        struct midgard_disasm_stats stats =
                pandecode_shader_disassemble(shader, job_no, job_type, is_bifrost, gpu_id);

        bool has_texture = (stats.texture_count > 0);
        bool has_sampler = (stats.sampler_count > 0);
        bool has_attribute = (stats.attribute_count > 0);
        bool has_varying = (stats.varying_count > 0);
        bool has_uniform = (stats.uniform_count > 0);
        bool has_ubo = (stats.uniform_buffer_count > 0);

        if (has_texture || has_sampler)
                pandecode_msg("XXX: blend shader accessing textures\n");

        if (has_attribute || has_varying)
                pandecode_msg("XXX: blend shader accessing interstage\n");

        if (has_uniform || has_ubo)
                pandecode_msg("XXX: blend shader accessing uniforms\n");
}

static void
pandecode_textures(mali_ptr textures, unsigned texture_count, int job_no, bool is_bifrost)
{
        struct pandecode_mapped_memory *mmem = pandecode_find_mapped_gpu_mem_containing(textures);

        if (!mmem)
                return;

        if (is_bifrost) {
                const struct bifrost_texture_descriptor *PANDECODE_PTR_VAR(t, mmem, textures);

                pandecode_log("uint64_t textures_%"PRIx64"_%d[] = {\n", textures, job_no);
                pandecode_indent++;

                for (unsigned tex = 0; tex < texture_count; ++tex)
                        pandecode_bifrost_texture(&t[tex], job_no, tex);

                pandecode_indent--;
                pandecode_log("};\n");
        } else {
                mali_ptr *PANDECODE_PTR_VAR(u, mmem, textures);

                pandecode_log("uint64_t textures_%"PRIx64"_%d[] = {\n", textures, job_no);
                pandecode_indent++;

                for (int tex = 0; tex < texture_count; ++tex) {
                        mali_ptr *PANDECODE_PTR_VAR(u, mmem, textures + tex * sizeof(mali_ptr));
                        char *a = pointer_as_memory_reference(*u);
                        pandecode_log("%s,\n", a);
                        free(a);
                }

                pandecode_indent--;
                pandecode_log("};\n");

                /* Now, finally, descend down into the texture descriptor */
                for (unsigned tex = 0; tex < texture_count; ++tex) {
                        mali_ptr *PANDECODE_PTR_VAR(u, mmem, textures + tex * sizeof(mali_ptr));
                        struct pandecode_mapped_memory *tmem = pandecode_find_mapped_gpu_mem_containing(*u);
                        if (tmem)
                                pandecode_texture(*u, tmem, job_no, tex);
                }
        }
}

static void
pandecode_samplers(mali_ptr samplers, unsigned sampler_count, int job_no, bool is_bifrost)
{
        struct pandecode_mapped_memory *smem = pandecode_find_mapped_gpu_mem_containing(samplers);

        if (!smem)
                return;

        if (is_bifrost) {
                struct bifrost_sampler_descriptor *s;

                for (int i = 0; i < sampler_count; ++i) {
                        s = pandecode_fetch_gpu_mem(smem, samplers + sizeof(*s) * i, sizeof(*s));

                        pandecode_log("struct bifrost_sampler_descriptor sampler_descriptor_%"PRIx64"_%d_%d = {\n", samplers + sizeof(*s) * i, job_no, i);
                        pandecode_indent++;

                        if (s->unk1 != 1) {
                                pandecode_msg("XXX: unk1 tripped\n");
                                pandecode_prop("unk1 = 0x%x", s->unk1);
                        }

                        pandecode_prop("wrap_s = %s", pandecode_wrap_mode(s->wrap_s));
                        pandecode_prop("wrap_t = %s", pandecode_wrap_mode(s->wrap_t));
                        pandecode_prop("wrap_r = %s", pandecode_wrap_mode(s->wrap_r));

                        if (s->unk1 != 0x8) {
                                pandecode_msg("XXX: unk8 tripped\n");
                                pandecode_prop("unk8 = 0x%x", s->unk8);
                        }

                        if (s->unk2 != 2) {
                                pandecode_msg("XXX: unk2 tripped\n");
                                pandecode_prop("unk2 = 0x%x", s->unk2);
                        }

                        pandecode_prop("min_filter = %s", s->min_filter ? "nearest" : "linear");
                        pandecode_prop("norm_coords = 0x%x", s->norm_coords & 0x1);
                        pandecode_prop("zero1 = 0x%x", s->zero1 & 0x1);
                        pandecode_prop("mip_filter = %s", s->mip_filter ? "linear" : "nearest");
                        pandecode_prop("mag_filter = %s", s->mag_filter ? "linear" : "nearest");

                        pandecode_prop("min_lod = FIXED_16(%f)", DECODE_FIXED_16(s->min_lod));
                        pandecode_prop("max_lod = FIXED_16(%f)", DECODE_FIXED_16(s->max_lod));

                        if (s->zero1 || s->zero2 || s->zero3 || s->zero4 || s->zero5) {
                                pandecode_msg("XXX: sampler zero tripped\n");
                                pandecode_prop("zero = 0x%X, 0x%X, 0x%X, 0x%X, 0x%X\n", s->zero1, s->zero2, s->zero3, s->zero4, s->zero5);
                        }

                        pandecode_indent--;
                        pandecode_log("};\n");
                }
        } else {
                struct mali_sampler_descriptor *s;

                for (int i = 0; i < sampler_count; ++i) {
                        s = pandecode_fetch_gpu_mem(smem, samplers + sizeof(*s) * i, sizeof(*s));

                        pandecode_log("struct mali_sampler_descriptor sampler_descriptor_%"PRIx64"_%d_%d = {\n", samplers + sizeof(*s) * i, job_no, i);
                        pandecode_indent++;

                        pandecode_log(".filter_mode = ");
                        pandecode_log_decoded_flags(sampler_flag_info, s->filter_mode);
                        pandecode_log_cont(",\n");

                        pandecode_prop("min_lod = FIXED_16(%f)", DECODE_FIXED_16(s->min_lod));
                        pandecode_prop("max_lod = FIXED_16(%f)", DECODE_FIXED_16(s->max_lod));

                        if (s->lod_bias)
                                pandecode_prop("lod_bias = FIXED_16(%f)", DECODE_FIXED_16(s->lod_bias));

                        pandecode_prop("wrap_s = %s", pandecode_wrap_mode(s->wrap_s));
                        pandecode_prop("wrap_t = %s", pandecode_wrap_mode(s->wrap_t));
                        pandecode_prop("wrap_r = %s", pandecode_wrap_mode(s->wrap_r));

                        pandecode_prop("compare_func = %s", pandecode_func(s->compare_func));

                        if (s->zero || s->zero2) {
                                pandecode_msg("XXX: sampler zero tripped\n");
                                pandecode_prop("zero = 0x%X, 0x%X\n", s->zero, s->zero2);
                        }

                        pandecode_prop("seamless_cube_map = %d", s->seamless_cube_map);

                        pandecode_prop("border_color = { %f, %f, %f, %f }",
                                       s->border_color[0],
                                       s->border_color[1],
                                       s->border_color[2],
                                       s->border_color[3]);

                        pandecode_indent--;
                        pandecode_log("};\n");
                }
        }
}

static void
pandecode_vertex_tiler_postfix_pre(
                const struct mali_vertex_tiler_postfix *p,
                int job_no, enum mali_job_type job_type,
                char *suffix, bool is_bifrost, unsigned gpu_id)
{
        struct pandecode_mapped_memory *attr_mem;

        /* On Bifrost, since the tiler heap (for tiler jobs) and the scratchpad
         * are the only things actually needed from the FBD, vertex/tiler jobs
         * no longer reference the FBD -- instead, this field points to some
         * info about the scratchpad.
         */

        struct pandecode_fbd fbd_info = {
                /* Default for Bifrost */
                .rt_count = 1
        };

        if (is_bifrost) {
                pandecode_log_cont("\t/* %X %/\n", p->shared_memory & 1);
                pandecode_compute_fbd(p->shared_memory & ~1, job_no);
        } else if (p->shared_memory & MALI_MFBD)
                fbd_info = pandecode_mfbd_bfr((u64) ((uintptr_t) p->shared_memory) & FBD_MASK, job_no, false, job_type == JOB_TYPE_COMPUTE, false);
        else if (job_type == JOB_TYPE_COMPUTE)
                pandecode_compute_fbd((u64) (uintptr_t) p->shared_memory, job_no);
        else
                fbd_info = pandecode_sfbd((u64) (uintptr_t) p->shared_memory, job_no, false, gpu_id);

        int varying_count = 0, attribute_count = 0, uniform_count = 0, uniform_buffer_count = 0;
        int texture_count = 0, sampler_count = 0;

        if (p->shader) {
                struct pandecode_mapped_memory *smem = pandecode_find_mapped_gpu_mem_containing(p->shader);
                struct mali_shader_meta *PANDECODE_PTR_VAR(s, smem, p->shader);

                /* Disassemble ahead-of-time to get stats. Initialize with
                 * stats for the missing-shader case so we get validation
                 * there, too */

                struct midgard_disasm_stats info = {
                        .texture_count = 0,
                        .sampler_count = 0,
                        .attribute_count = 0,
                        .varying_count = 0,
                        .work_count = 1,

                        .uniform_count = -128,
                        .uniform_buffer_count = 0
                };

                if (s->shader & ~0xF)
                        info = pandecode_shader_disassemble(s->shader & ~0xF, job_no, job_type, is_bifrost, gpu_id);

                pandecode_log("struct mali_shader_meta shader_meta_%"PRIx64"_%d%s = {\n", p->shader, job_no, suffix);
                pandecode_indent++;

                /* Save for dumps */
                attribute_count = s->attribute_count;
                varying_count = s->varying_count;
                texture_count = s->texture_count;
                sampler_count = s->sampler_count;

                if (is_bifrost) {
                        uniform_count = s->bifrost2.uniform_count;
                        uniform_buffer_count = s->bifrost1.uniform_buffer_count;
                } else {
                        uniform_count = s->midgard1.uniform_count;
                        uniform_buffer_count = s->midgard1.uniform_buffer_count;
                }

                pandecode_shader_address("shader", s->shader);

                pandecode_shader_prop("texture_count", s->texture_count, info.texture_count, false);
                pandecode_shader_prop("sampler_count", s->sampler_count, info.sampler_count, false);
                pandecode_shader_prop("attribute_count", s->attribute_count, info.attribute_count, false);
                pandecode_shader_prop("varying_count", s->varying_count, info.varying_count, false);
                pandecode_shader_prop("uniform_buffer_count",
                                uniform_buffer_count,
                                info.uniform_buffer_count, true);

                if (!is_bifrost) {
                        pandecode_shader_prop("uniform_count",
                                        uniform_count,
                                        info.uniform_count, false);

                        pandecode_shader_prop("work_count",
                                        s->midgard1.work_count, info.work_count, false);
                }

                if (is_bifrost) {
                        pandecode_prop("bifrost1.unk1 = 0x%" PRIx32, s->bifrost1.unk1);
                } else {
                        bool helpers = s->midgard1.flags_lo & MALI_HELPER_INVOCATIONS;
                        s->midgard1.flags_lo &= ~MALI_HELPER_INVOCATIONS;

                        if (helpers != info.helper_invocations) {
                                pandecode_msg("XXX: expected helpers %u but got %u\n",
                                                info.helper_invocations, helpers);
                        }

                        pandecode_log(".midgard1.flags_lo = ");
                        pandecode_log_decoded_flags(shader_midgard1_flag_lo_info, s->midgard1.flags_lo);
                        pandecode_log_cont(",\n");

                        pandecode_log(".midgard1.flags_hi = ");
                        pandecode_log_decoded_flags(shader_midgard1_flag_hi_info, s->midgard1.flags_hi);
                        pandecode_log_cont(",\n");
                }

                if (s->depth_units || s->depth_factor) {
                        pandecode_prop("depth_factor = %f", s->depth_factor);
                        pandecode_prop("depth_units = %f", s->depth_units);
                }

                if (s->alpha_coverage) {
                        bool invert_alpha_coverage = s->alpha_coverage & 0xFFF0;
                        uint16_t inverted_coverage = invert_alpha_coverage ? ~s->alpha_coverage : s->alpha_coverage;

                        pandecode_prop("alpha_coverage = %sMALI_ALPHA_COVERAGE(%f)",
                                       invert_alpha_coverage ? "~" : "",
                                       MALI_GET_ALPHA_COVERAGE(inverted_coverage));
                }

                if (s->unknown2_3 || s->unknown2_4) {
                        pandecode_log(".unknown2_3 = ");

                        int unknown2_3 = s->unknown2_3;
                        int unknown2_4 = s->unknown2_4;

                        /* We're not quite sure what these flags mean without the depth test, if anything */

                        if (unknown2_3 & (MALI_DEPTH_WRITEMASK | MALI_DEPTH_FUNC_MASK)) {
                                const char *func = pandecode_func(MALI_GET_DEPTH_FUNC(unknown2_3));
                                unknown2_3 &= ~MALI_DEPTH_FUNC_MASK;

                                pandecode_log_cont("MALI_DEPTH_FUNC(%s) | ", func);
                        }

                        pandecode_log_decoded_flags(u3_flag_info, unknown2_3);
                        pandecode_log_cont(",\n");

                        pandecode_log(".unknown2_4 = ");
                        pandecode_log_decoded_flags(u4_flag_info, unknown2_4);
                        pandecode_log_cont(",\n");
                }

                if (s->stencil_mask_front || s->stencil_mask_back) {
                        pandecode_prop("stencil_mask_front = 0x%02X", s->stencil_mask_front);
                        pandecode_prop("stencil_mask_back = 0x%02X", s->stencil_mask_back);
                }

                pandecode_stencil("front", &s->stencil_front);
                pandecode_stencil("back", &s->stencil_back);

                if (is_bifrost) {
                        pandecode_log(".bifrost2 = {\n");
                        pandecode_indent++;

                        pandecode_prop("unk3 = 0x%" PRIx32, s->bifrost2.unk3);
                        pandecode_prop("preload_regs = 0x%" PRIx32, s->bifrost2.preload_regs);
                        pandecode_prop("uniform_count = %" PRId32, s->bifrost2.uniform_count);
                        pandecode_prop("unk4 = 0x%" PRIx32, s->bifrost2.unk4);

                        pandecode_indent--;
                        pandecode_log("},\n");
                } else if (s->midgard2.unknown2_7) {
                        pandecode_log(".midgard2 = {\n");
                        pandecode_indent++;

                        pandecode_prop("unknown2_7 = 0x%" PRIx32, s->midgard2.unknown2_7);
                        pandecode_indent--;
                        pandecode_log("},\n");
                }

                if (s->padding) {
                        pandecode_msg("XXX: shader padding tripped\n");
                        pandecode_prop("padding = 0x%" PRIx32, s->padding);
                }

                if (!is_bifrost) {
                        /* TODO: Blend shaders routing/disasm */
                        union midgard_blend blend = s->blend;
                        mali_ptr shader = pandecode_midgard_blend(&blend, s->unknown2_3 & MALI_HAS_BLEND_SHADER);
                        if (shader & ~0xF)
                                pandecode_blend_shader_disassemble(shader, job_no, job_type, false, gpu_id);
                }

                pandecode_indent--;
                pandecode_log("};\n");

                /* MRT blend fields are used whenever MFBD is used, with
                 * per-RT descriptors */

                if (job_type == JOB_TYPE_TILER && (is_bifrost || p->shared_memory & MALI_MFBD)) {
                        void* blend_base = (void *) (s + 1);

                        for (unsigned i = 0; i < fbd_info.rt_count; i++) {
                                mali_ptr shader = 0;

                                if (is_bifrost)
                                        shader = pandecode_bifrost_blend(blend_base, job_no, i);
                                else
                                        shader = pandecode_midgard_blend_mrt(blend_base, job_no, i);

                                if (shader & ~0xF)
                                        pandecode_blend_shader_disassemble(shader, job_no, job_type, false, gpu_id);

                        }
                }
        } else
                pandecode_msg("XXX: missing shader descriptor\n");

        if (p->viewport) {
                struct pandecode_mapped_memory *fmem = pandecode_find_mapped_gpu_mem_containing(p->viewport);
                struct mali_viewport *PANDECODE_PTR_VAR(f, fmem, p->viewport);

                pandecode_log("struct mali_viewport viewport_%"PRIx64"_%d%s = {\n", p->viewport, job_no, suffix);
                pandecode_indent++;

                pandecode_prop("clip_minx = %f", f->clip_minx);
                pandecode_prop("clip_miny = %f", f->clip_miny);
                pandecode_prop("clip_minz = %f", f->clip_minz);
                pandecode_prop("clip_maxx = %f", f->clip_maxx);
                pandecode_prop("clip_maxy = %f", f->clip_maxy);
                pandecode_prop("clip_maxz = %f", f->clip_maxz);

                /* Only the higher coordinates are MALI_POSITIVE scaled */

                pandecode_prop("viewport0 = { %d, %d }",
                               f->viewport0[0], f->viewport0[1]);

                pandecode_prop("viewport1 = { MALI_POSITIVE(%d), MALI_POSITIVE(%d) }",
                               f->viewport1[0] + 1, f->viewport1[1] + 1);

                pandecode_indent--;
                pandecode_log("};\n");
        }

        unsigned max_attr_index = 0;

        if (p->attribute_meta)
                max_attr_index = pandecode_attribute_meta(job_no, attribute_count, p, false, suffix);

        if (p->attributes) {
                attr_mem = pandecode_find_mapped_gpu_mem_containing(p->attributes);
                pandecode_attributes(attr_mem, p->attributes, job_no, suffix, max_attr_index, false, job_type);
        }

        /* Varyings are encoded like attributes but not actually sent; we just
         * pass a zero buffer with the right stride/size set, (or whatever)
         * since the GPU will write to it itself */

        if (p->varying_meta) {
                varying_count = pandecode_attribute_meta(job_no, varying_count, p, true, suffix);
        }

        if (p->varyings) {
                attr_mem = pandecode_find_mapped_gpu_mem_containing(p->varyings);

                /* Number of descriptors depends on whether there are
                 * non-internal varyings */

                pandecode_attributes(attr_mem, p->varyings, job_no, suffix, varying_count, true, job_type);
        }

        if (p->uniform_buffers) {
                if (uniform_buffer_count)
                        pandecode_uniform_buffers(p->uniform_buffers, uniform_buffer_count, job_no);
                else
                        pandecode_msg("warn: UBOs specified but not referenced\n");
        } else if (uniform_buffer_count)
                pandecode_msg("XXX: UBOs referenced but not specified\n");

        /* We don't want to actually dump uniforms, but we do need to validate
         * that the counts we were given are sane */

        if (p->uniforms) {
                if (uniform_count)
                        pandecode_uniforms(p->uniforms, uniform_count);
                else
                        pandecode_msg("warn: Uniforms specified but not referenced\n");
        } else if (uniform_count)
                pandecode_msg("XXX: Uniforms referenced but not specified\n");

        if (p->textures)
                pandecode_textures(p->textures, texture_count, job_no, is_bifrost);

        if (p->sampler_descriptor)
                pandecode_samplers(p->sampler_descriptor, sampler_count, job_no, is_bifrost);
}

static void
pandecode_gl_enables(uint32_t gl_enables, int job_type)
{
        pandecode_log(".gl_enables = ");

        pandecode_log_decoded_flags(gl_enable_flag_info, gl_enables);

        pandecode_log_cont(",\n");
}

static void
pandecode_vertex_tiler_postfix(const struct mali_vertex_tiler_postfix *p, int job_no, bool is_bifrost)
{
        if (p->shader & 0xF)
                pandecode_msg("warn: shader tagged %X\n", (unsigned) (p->shader & 0xF));

        pandecode_log(".postfix = {\n");
        pandecode_indent++;

        pandecode_gl_enables(p->gl_enables, JOB_TYPE_TILER);
        pandecode_prop("instance_shift = 0x%x", p->instance_shift);
        pandecode_prop("instance_odd = 0x%x", p->instance_odd);

        if (p->zero4) {
                pandecode_msg("XXX: vertex only zero tripped");
                pandecode_prop("zero4 = 0x%" PRIx32, p->zero4);
        }

        pandecode_prop("offset_start = 0x%x", p->offset_start);

        if (p->zero5) {
                pandecode_msg("XXX: vertex only zero tripped");
                pandecode_prop("zero5 = 0x%" PRIx32, p->zero5);
        }

        MEMORY_PROP(p, position_varying);
        MEMORY_PROP(p, occlusion_counter);

        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_tiler_heap_meta(mali_ptr gpu_va, int job_no)
{
        struct pandecode_mapped_memory *mem = pandecode_find_mapped_gpu_mem_containing(gpu_va);
        const struct bifrost_tiler_heap_meta *PANDECODE_PTR_VAR(h, mem, gpu_va);

        pandecode_log("struct bifrost_tiler_heap_meta tiler_heap_meta_%"PRIx64"_%d = {\n", gpu_va, job_no);
        pandecode_indent++;

        if (h->zero) {
                pandecode_msg("XXX: tiler heap zero tripped\n");
                pandecode_prop("zero = 0x%x", h->zero);
        }

        pandecode_prop("heap_size = 0x%x", h->heap_size);
        MEMORY_PROP(h, tiler_heap_start);
        MEMORY_PROP(h, tiler_heap_free);

        /* this might point to the beginning of another buffer, when it's
         * really the end of the tiler heap buffer, so we have to be careful
         * here. but for zero length, we need the same pointer.
         */

        if (h->tiler_heap_end == h->tiler_heap_start) {
                MEMORY_PROP(h, tiler_heap_start);
        } else {
                char *a = pointer_as_memory_reference(h->tiler_heap_end - 1);
                pandecode_prop("tiler_heap_end = %s + 1", a);
                free(a);
        }

        for (int i = 0; i < 10; i++) {
                if (h->zeros[i] != 0) {
                        pandecode_msg("XXX: tiler heap zero %d tripped, value %x\n",
                                      i, h->zeros[i]);
                }
        }

        if (h->unk1 != 0x1) {
                pandecode_msg("XXX: tiler heap unk1 tripped\n");
                pandecode_prop("unk1 = 0x%x", h->unk1);
        }

        if (h->unk7e007e != 0x7e007e) {
                pandecode_msg("XXX: tiler heap unk7e007e tripped\n");
                pandecode_prop("unk7e007e = 0x%x", h->unk7e007e);
        }

        pandecode_indent--;
        pandecode_log("};\n");
}

static void
pandecode_tiler_meta(mali_ptr gpu_va, int job_no)
{
        struct pandecode_mapped_memory *mem = pandecode_find_mapped_gpu_mem_containing(gpu_va);
        const struct bifrost_tiler_meta *PANDECODE_PTR_VAR(t, mem, gpu_va);

        pandecode_tiler_heap_meta(t->tiler_heap_meta, job_no);

        pandecode_log("struct bifrost_tiler_meta tiler_meta_%"PRIx64"_%d = {\n", gpu_va, job_no);
        pandecode_indent++;

        if (t->zero0 || t->zero1) {
                pandecode_msg("XXX: tiler meta zero tripped\n");
                pandecode_prop("zero0 = 0x%" PRIx64, t->zero0);
                pandecode_prop("zero1 = 0x%" PRIx64, t->zero1);
        }

        if (t->hierarchy_mask != 0xa &&
            t->hierarchy_mask != 0x14 &&
            t->hierarchy_mask != 0x28 &&
            t->hierarchy_mask != 0x50 &&
            t->hierarchy_mask != 0xa0)
                pandecode_prop("XXX: Unexpected hierarchy_mask (not 0xa, 0x14, 0x28, 0x50 or 0xa0)!");

        pandecode_prop("hierarchy_mask = 0x%" PRIx16, t->hierarchy_mask);

        pandecode_prop("flags = 0x%" PRIx16, t->flags);

        pandecode_prop("width = MALI_POSITIVE(%d)", t->width + 1);
        pandecode_prop("height = MALI_POSITIVE(%d)", t->height + 1);

        for (int i = 0; i < 12; i++) {
                if (t->zeros[i] != 0) {
                        pandecode_msg("XXX: tiler heap zero %d tripped, value %" PRIx64 "\n",
                                      i, t->zeros[i]);
                }
        }

        pandecode_indent--;
        pandecode_log("};\n");
}

static void
pandecode_primitive_size(union midgard_primitive_size u, bool constant)
{
        if (u.pointer == 0x0)
                return;

        pandecode_log(".primitive_size = {\n");
        pandecode_indent++;

        if (constant) {
                pandecode_prop("constant = %f", u.constant);
        } else {
                MEMORY_PROP((&u), pointer);
        }

        pandecode_indent--;
        pandecode_log("},\n");
}

static void
pandecode_tiler_only_bfr(const struct bifrost_tiler_only *t, int job_no)
{
        pandecode_log_cont("{\n");
        pandecode_indent++;

        /* TODO: gl_PointSize on Bifrost */
        pandecode_primitive_size(t->primitive_size, true);

        if (t->zero1 || t->zero2 || t->zero3 || t->zero4 || t->zero5
            || t->zero6) {
                pandecode_msg("XXX: tiler only zero tripped\n");
                pandecode_prop("zero1 = 0x%" PRIx64, t->zero1);
                pandecode_prop("zero2 = 0x%" PRIx64, t->zero2);
                pandecode_prop("zero3 = 0x%" PRIx64, t->zero3);
                pandecode_prop("zero4 = 0x%" PRIx64, t->zero4);
                pandecode_prop("zero5 = 0x%" PRIx64, t->zero5);
                pandecode_prop("zero6 = 0x%" PRIx64, t->zero6);
        }

        pandecode_indent--;
        pandecode_log("},\n");
}

static int
pandecode_vertex_job_bfr(const struct mali_job_descriptor_header *h,
                                const struct pandecode_mapped_memory *mem,
                                mali_ptr payload, int job_no, unsigned gpu_id)
{
        struct bifrost_payload_vertex *PANDECODE_PTR_VAR(v, mem, payload);

        pandecode_vertex_tiler_postfix_pre(&v->postfix, job_no, h->job_type, "", true, gpu_id);

        pandecode_log("struct bifrost_payload_vertex payload_%"PRIx64"_%d = {\n", payload, job_no);
        pandecode_indent++;

        pandecode_vertex_tiler_prefix(&v->prefix, job_no, false);
        pandecode_vertex_tiler_postfix(&v->postfix, job_no, true);

        pandecode_indent--;
        pandecode_log("};\n");

        return sizeof(*v);
}

static int
pandecode_tiler_job_bfr(const struct mali_job_descriptor_header *h,
                               const struct pandecode_mapped_memory *mem,
                               mali_ptr payload, int job_no, unsigned gpu_id)
{
        struct bifrost_payload_tiler *PANDECODE_PTR_VAR(t, mem, payload);

        pandecode_vertex_tiler_postfix_pre(&t->postfix, job_no, h->job_type, "", true, gpu_id);
        pandecode_tiler_meta(t->tiler.tiler_meta, job_no);

        pandecode_log("struct bifrost_payload_tiler payload_%"PRIx64"_%d = {\n", payload, job_no);
        pandecode_indent++;

        pandecode_vertex_tiler_prefix(&t->prefix, job_no, false);

        pandecode_log(".tiler = ");
        pandecode_tiler_only_bfr(&t->tiler, job_no);

        pandecode_vertex_tiler_postfix(&t->postfix, job_no, true);

        pandecode_indent--;
        pandecode_log("};\n");

        return sizeof(*t);
}

static int
pandecode_vertex_or_tiler_job_mdg(const struct mali_job_descriptor_header *h,
                const struct pandecode_mapped_memory *mem,
                mali_ptr payload, int job_no, unsigned gpu_id)
{
        struct midgard_payload_vertex_tiler *PANDECODE_PTR_VAR(v, mem, payload);
        bool is_graphics = (h->job_type == JOB_TYPE_VERTEX) || (h->job_type == JOB_TYPE_TILER);

        pandecode_vertex_tiler_postfix_pre(&v->postfix, job_no, h->job_type, "", false, gpu_id);

        pandecode_log("struct midgard_payload_vertex_tiler payload_%d = {\n", job_no);
        pandecode_indent++;

        pandecode_vertex_tiler_prefix(&v->prefix, job_no, is_graphics);
        pandecode_vertex_tiler_postfix(&v->postfix, job_no, false);

        bool has_primitive_pointer = v->prefix.unknown_draw & MALI_DRAW_VARYING_SIZE;
        pandecode_primitive_size(v->primitive_size, !has_primitive_pointer);

        pandecode_indent--;
        pandecode_log("};\n");

        return sizeof(*v);
}

static int
pandecode_fragment_job(const struct pandecode_mapped_memory *mem,
                              mali_ptr payload, int job_no,
                              bool is_bifrost, unsigned gpu_id)
{
        const struct mali_payload_fragment *PANDECODE_PTR_VAR(s, mem, payload);

        bool is_mfbd = s->framebuffer & MALI_MFBD;

        if (!is_mfbd && is_bifrost)
                pandecode_msg("XXX: Bifrost fragment must use MFBD\n");

        struct pandecode_fbd info;

        if (is_mfbd)
                info = pandecode_mfbd_bfr(s->framebuffer & FBD_MASK, job_no, true, false, is_bifrost);
        else
                info = pandecode_sfbd(s->framebuffer & FBD_MASK, job_no, true, gpu_id);

        /* Compute the tag for the tagged pointer. This contains the type of
         * FBD (MFBD/SFBD), and in the case of an MFBD, information about which
         * additional structures follow the MFBD header (an extra payload or
         * not, as well as a count of render targets) */

        unsigned expected_tag = is_mfbd ? MALI_MFBD : 0;

        if (is_mfbd) {
                if (info.has_extra)
                        expected_tag |= MALI_MFBD_TAG_EXTRA;

                expected_tag |= (MALI_POSITIVE(info.rt_count) << 2);
        }

        if ((s->min_tile_coord | s->max_tile_coord) & ~(MALI_X_COORD_MASK | MALI_Y_COORD_MASK)) {
                pandecode_msg("XXX: unexpected tile coordinate bits\n");
                pandecode_prop("min_tile_coord = 0x%X\n", s->min_tile_coord);
                pandecode_prop("max_tile_coord = 0x%X\n", s->min_tile_coord);
        }

        /* Extract tile coordinates */

        unsigned min_x = MALI_TILE_COORD_X(s->min_tile_coord) << MALI_TILE_SHIFT;
        unsigned min_y = MALI_TILE_COORD_Y(s->min_tile_coord) << MALI_TILE_SHIFT;

        unsigned max_x = (MALI_TILE_COORD_X(s->max_tile_coord) + 1) << MALI_TILE_SHIFT;
        unsigned max_y = (MALI_TILE_COORD_Y(s->max_tile_coord) + 1) << MALI_TILE_SHIFT;

        /* For the max, we also want the floored (rather than ceiled) version for checking */

        unsigned max_x_f = (MALI_TILE_COORD_X(s->max_tile_coord)) << MALI_TILE_SHIFT;
        unsigned max_y_f = (MALI_TILE_COORD_Y(s->max_tile_coord)) << MALI_TILE_SHIFT;

        /* Validate the coordinates are well-ordered */

        if (min_x == max_x)
                pandecode_msg("XXX: empty X coordinates (%u = %u)\n", min_x, max_x);
        else if (min_x > max_x)
                pandecode_msg("XXX: misordered X coordinates (%u > %u)\n", min_x, max_x);

        if (min_y == max_y)
                pandecode_msg("XXX: empty X coordinates (%u = %u)\n", min_x, max_x);
        else if (min_y > max_y)
                pandecode_msg("XXX: misordered X coordinates (%u > %u)\n", min_x, max_x);

        /* Validate the coordinates fit inside the framebuffer. We use floor,
         * rather than ceil, for the max coordinates, since the tile
         * coordinates for something like an 800x600 framebuffer will actually
         * resolve to 800x608, which would otherwise trigger a Y-overflow */

        if ((min_x > info.width) || (max_x_f > info.width))
                pandecode_msg("XXX: tile coordinates overflow in X direction\n");

        if ((min_y > info.height) || (max_y_f > info.height))
                pandecode_msg("XXX: tile coordinates overflow in Y direction\n");

        /* After validation, we print */

        pandecode_log("fragment (%u, %u) ... (%u, %u)\n\n", min_x, min_y, max_x, max_y);

        /* The FBD is a tagged pointer */

        unsigned tag = (s->framebuffer & ~FBD_MASK);

        if (tag != expected_tag)
                pandecode_msg("XXX: expected FBD tag %X but got %X\n", expected_tag, tag);

        return sizeof(*s);
}

/* Entrypoint to start tracing. jc_gpu_va is the GPU address for the first job
 * in the chain; later jobs are found by walking the chain. Bifrost is, well,
 * if it's bifrost or not. GPU ID is the more finegrained ID (at some point, we
 * might wish to combine this with the bifrost parameter) because some details
 * are model-specific even within a particular architecture. Minimal traces
 * *only* examine the job descriptors, skipping printing entirely if there is
 * no faults, and only descends into the payload if there are faults. This is
 * useful for looking for faults without the overhead of invasive traces. */

void
pandecode_jc(mali_ptr jc_gpu_va, bool bifrost, unsigned gpu_id, bool minimal)
{
        struct mali_job_descriptor_header *h;
        unsigned job_descriptor_number = 0;

        do {
                struct pandecode_mapped_memory *mem =
                        pandecode_find_mapped_gpu_mem_containing(jc_gpu_va);

                void *payload;

                h = PANDECODE_PTR(mem, jc_gpu_va, struct mali_job_descriptor_header);

                /* On Midgard, for 32-bit jobs except for fragment jobs, the
                 * high 32-bits of the 64-bit pointer are reused to store
                 * something else.
                 */
                int offset = h->job_descriptor_size == MALI_JOB_32 &&
                             h->job_type != JOB_TYPE_FRAGMENT ? 4 : 0;
                mali_ptr payload_ptr = jc_gpu_va + sizeof(*h) - offset;

                payload = pandecode_fetch_gpu_mem(mem, payload_ptr, 256);

                int job_no = job_descriptor_number++;

                /* If the job is good to go, skip it in minimal mode */
                if (minimal && (h->exception_status == 0x0 || h->exception_status == 0x1))
                        continue;

                pandecode_log("struct mali_job_descriptor_header job_%"PRIx64"_%d = {\n", jc_gpu_va, job_no);
                pandecode_indent++;

                pandecode_prop("job_type = %s", pandecode_job_type(h->job_type));

                if (h->job_descriptor_size)
                        pandecode_prop("job_descriptor_size = %d", h->job_descriptor_size);

                if (h->exception_status && h->exception_status != 0x1)
                        pandecode_prop("exception_status = %x (source ID: 0x%x access: %s exception: 0x%x)",
                                       h->exception_status,
                                       (h->exception_status >> 16) & 0xFFFF,
                                       pandecode_exception_access((h->exception_status >> 8) & 0x3),
                                       h->exception_status  & 0xFF);

                if (h->first_incomplete_task)
                        pandecode_prop("first_incomplete_task = %d", h->first_incomplete_task);

                if (h->fault_pointer)
                        pandecode_prop("fault_pointer = 0x%" PRIx64, h->fault_pointer);

                if (h->job_barrier)
                        pandecode_prop("job_barrier = %d", h->job_barrier);

                pandecode_prop("job_index = %d", h->job_index);

                if (h->unknown_flags)
                        pandecode_prop("unknown_flags = %d", h->unknown_flags);

                if (h->job_dependency_index_1)
                        pandecode_prop("job_dependency_index_1 = %d", h->job_dependency_index_1);

                if (h->job_dependency_index_2)
                        pandecode_prop("job_dependency_index_2 = %d", h->job_dependency_index_2);

                pandecode_indent--;
                pandecode_log("};\n");

                switch (h->job_type) {
                case JOB_TYPE_WRITE_VALUE: {
                        struct mali_payload_write_value *s = payload;
                        pandecode_log("struct mali_payload_write_value payload_%"PRIx64"_%d = {\n", payload_ptr, job_no);
                        pandecode_indent++;
                        MEMORY_PROP(s, address);

                        if (s->value_descriptor != MALI_WRITE_VALUE_ZERO) {
                                pandecode_msg("XXX: unknown value descriptor\n");
                                pandecode_prop("value_descriptor = 0x%" PRIX32, s->value_descriptor);
                        }

                        if (s->reserved) {
                                pandecode_msg("XXX: set value tripped\n");
                                pandecode_prop("reserved = 0x%" PRIX32, s->reserved);
                        }

                        pandecode_prop("immediate = 0x%" PRIX64, s->immediate);
                        pandecode_indent--;
                        pandecode_log("};\n");

                        break;
                }

                case JOB_TYPE_TILER:
                case JOB_TYPE_VERTEX:
                case JOB_TYPE_COMPUTE:
                        if (bifrost) {
                                if (h->job_type == JOB_TYPE_TILER)
                                        pandecode_tiler_job_bfr(h, mem, payload_ptr, job_no, gpu_id);
                                else
                                        pandecode_vertex_job_bfr(h, mem, payload_ptr, job_no, gpu_id);
                        } else
                                pandecode_vertex_or_tiler_job_mdg(h, mem, payload_ptr, job_no, gpu_id);

                        break;

                case JOB_TYPE_FRAGMENT:
                        pandecode_fragment_job(mem, payload_ptr, job_no, bifrost, gpu_id);
                        break;

                default:
                        break;
                }
        } while ((jc_gpu_va = h->next_job));
}
