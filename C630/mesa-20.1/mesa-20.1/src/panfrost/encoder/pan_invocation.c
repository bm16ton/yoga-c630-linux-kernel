/*
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
 *
 * Authors (Collabora):
 *   Alyssa Rosenzweig <alyssa.rosenzweig@collabora.com>
 *
 */

#include <assert.h>
#include "util/u_math.h"
#include "pan_encoder.h"

/* Compute shaders are invoked with a gl_NumWorkGroups X/Y/Z triplet. Vertex
 * shaders, it turns out, are invoked with the same mechanism, with the triplet
 * (1, vertex_count, instance_count).
 *
 * Alongside this triplet is the gl_WorkGroupSize X/Y/Z triplet.
 *
 * Unfortunately, the packing for these triplet into the
 * mali_vertex_tiler_prefix is a little funky, using a dynamic bitfield. The
 * routines here exist to pack this */

void
panfrost_pack_work_groups_compute(
        struct mali_vertex_tiler_prefix *out,
        unsigned num_x,
        unsigned num_y,
        unsigned num_z,
        unsigned size_x,
        unsigned size_y,
        unsigned size_z,
        bool quirk_graphics)
{
        uint32_t packed = 0;

        /* The values needing packing, in order, and the corresponding shifts.
         * Indicies into shift are off-by-one to make the logic easier */

        unsigned shifts[7] = { 0 };

        unsigned values[6] = {
                MALI_POSITIVE(size_x),
                MALI_POSITIVE(size_y),
                MALI_POSITIVE(size_z),
                MALI_POSITIVE(num_x),
                MALI_POSITIVE(num_y),
                MALI_POSITIVE(num_z),
        };

        for (unsigned i = 0; i < 6; ++i) {
                /* OR it in, shifting as required */
                packed |= (values[i] << shifts[i]);

                /* How many bits did we use? */
                unsigned bit_count = util_logbase2_ceil(values[i] + 1);

                /* Set the next shift accordingly */
                shifts[i + 1] = shifts[i] + bit_count;
        }

        /* Quirk: for non-instanced graphics, the blob sets workgroups_z_shift
         * = 32. This doesn't appear to matter to the hardware, but it's good
         * to be bit-identical. */

        if (quirk_graphics && (num_z <= 1))
                shifts[5] = 32;

        /* Quirk: for graphics, workgroups_x_shift_2 must be at least 2,
         * whereas for OpenCL it is simply equal to workgroups_x_shift. For GL
         * compute, it is always 2 if no barriers are in use, but is equal to
         * workgroups_x_shift is barriers are in use. */

        unsigned shift_2 = shifts[3];

        if (quirk_graphics)
                shift_2 = MAX2(shift_2, 2);

        /* Pack them in */
        uint32_t packed_shifts =
                (shifts[1] << 0) |
                (shifts[2] << 5) |
                (shifts[3] << 10) |
                (shifts[4] << 16) |
                (shifts[5] << 22) |
                (shift_2 << 28);

        /* Upload the packed bitfields */
        out->invocation_count = packed;
        out->invocation_shifts = packed_shifts;

        /* TODO: Compute workgroups_x_shift_3 */
        out->workgroups_x_shift_3 = shift_2;
}

/* Packs vertex/tiler descriptors simultaneously */
void
panfrost_pack_work_groups_fused(
        struct mali_vertex_tiler_prefix *vertex,
        struct mali_vertex_tiler_prefix *tiler,
        unsigned num_x,
        unsigned num_y,
        unsigned num_z,
        unsigned size_x,
        unsigned size_y,
        unsigned size_z)
{
        panfrost_pack_work_groups_compute(vertex, num_x, num_y, num_z, size_x, size_y, size_z, true);

        /* Copy results over */
        tiler->invocation_count = vertex->invocation_count;
        tiler->invocation_shifts = vertex->invocation_shifts;

        /* Set special fields for each */
        vertex->workgroups_x_shift_3 = 5;
        tiler->workgroups_x_shift_3 = 6;
}

