/*
 * Copyright © 2017 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef IRIS_BATCH_DOT_H
#define IRIS_BATCH_DOT_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "util/u_dynarray.h"

#include "drm-uapi/i915_drm.h"
#include "common/gen_decoder.h"

#include "iris_fence.h"

/* The kernel assumes batchbuffers are smaller than 256kB. */
#define MAX_BATCH_SIZE (256 * 1024)

/* Terminating the batch takes either 4 bytes for MI_BATCH_BUFFER_END
 * or 12 bytes for MI_BATCH_BUFFER_START (when chaining).  Plus, we may
 * need an extra 4 bytes to pad out to the nearest QWord.  So reserve 16.
 */
#define BATCH_RESERVED 16

/* Our target batch size - flush approximately at this point. */
#define BATCH_SZ (64 * 1024 - BATCH_RESERVED)

enum iris_batch_name {
   IRIS_BATCH_RENDER,
   IRIS_BATCH_COMPUTE,
};

#define IRIS_BATCH_COUNT 2

struct iris_address {
   struct iris_bo *bo;
   uint64_t offset;
   bool write;
};

struct iris_batch {
   struct iris_screen *screen;
   struct pipe_debug_callback *dbg;
   struct pipe_device_reset_callback *reset;

   /** What batch is this? (e.g. IRIS_BATCH_RENDER/COMPUTE) */
   enum iris_batch_name name;

   /** Current batchbuffer being queued up. */
   struct iris_bo *bo;
   void *map;
   void *map_next;

   /** Size of the primary batch being submitted to execbuf (in bytes). */
   unsigned primary_batch_size;

   /** Total size of all chained batches (in bytes). */
   unsigned total_chained_batch_size;

   /** Last Surface State Base Address set in this hardware context. */
   uint64_t last_surface_base_address;

   uint32_t hw_ctx_id;

   /** The validation list */
   struct drm_i915_gem_exec_object2 *validation_list;
   struct iris_bo **exec_bos;
   int exec_count;
   int exec_array_size;

   /** Whether INTEL_BLACKHOLE_RENDER is enabled in the batch (aka first
    * instruction is a MI_BATCH_BUFFER_END).
    */
   bool noop_enabled;

   /**
    * A list of iris_syncpts associated with this batch.
    *
    * The first list entry will always be a signalling sync-point, indicating
    * that this batch has completed.  The others are likely to be sync-points
    * to wait on before executing the batch.
    */
   struct util_dynarray syncpts;

   /** A list of drm_i915_exec_fences to have execbuf signal or wait on */
   struct util_dynarray exec_fences;

   /** The amount of aperture space (in bytes) used by all exec_bos */
   int aperture_space;

   /** A sync-point for the last batch that was submitted. */
   struct iris_syncpt *last_syncpt;

   /** List of other batches which we might need to flush to use a BO */
   struct iris_batch *other_batches[IRIS_BATCH_COUNT - 1];

   struct {
      /**
       * Set of struct brw_bo * that have been rendered to within this
       * batchbuffer and would need flushing before being used from another
       * cache domain that isn't coherent with it (i.e. the sampler).
       */
      struct hash_table *render;

      /**
       * Set of struct brw_bo * that have been used as a depth buffer within
       * this batchbuffer and would need flushing before being used from
       * another cache domain that isn't coherent with it (i.e. the sampler).
       */
      struct set *depth;
   } cache;

   struct gen_batch_decode_ctx decoder;
   struct hash_table_u64 *state_sizes;

   /** Have we emitted any draw calls to this batch? */
   bool contains_draw;

   uint32_t last_aux_map_state;
};

void iris_init_batch(struct iris_batch *batch,
                     struct iris_screen *screen,
                     struct pipe_debug_callback *dbg,
                     struct pipe_device_reset_callback *reset,
                     struct hash_table_u64 *state_sizes,
                     struct iris_batch *all_batches,
                     enum iris_batch_name name,
                     int priority);
void iris_chain_to_new_batch(struct iris_batch *batch);
void iris_batch_free(struct iris_batch *batch);
void iris_batch_maybe_flush(struct iris_batch *batch, unsigned estimate);

void _iris_batch_flush(struct iris_batch *batch, const char *file, int line);
#define iris_batch_flush(batch) _iris_batch_flush((batch), __FILE__, __LINE__)

bool iris_batch_references(struct iris_batch *batch, struct iris_bo *bo);

uint64_t iris_batch_prepare_noop(struct iris_batch *batch,
                                 bool noop_enable,
                                 uint64_t dirty_flags);

#define RELOC_WRITE EXEC_OBJECT_WRITE

void iris_use_pinned_bo(struct iris_batch *batch, struct iris_bo *bo,
                        bool writable);

enum pipe_reset_status iris_batch_check_for_reset(struct iris_batch *batch);

static inline unsigned
iris_batch_bytes_used(struct iris_batch *batch)
{
   return batch->map_next - batch->map;
}

/**
 * Ensure the current command buffer has \param size bytes of space
 * remaining.  If not, this creates a secondary batch buffer and emits
 * a jump from the primary batch to the start of the secondary.
 *
 * Most callers want iris_get_command_space() instead.
 */
static inline void
iris_require_command_space(struct iris_batch *batch, unsigned size)
{
   const unsigned required_bytes = iris_batch_bytes_used(batch) + size;

   if (required_bytes >= BATCH_SZ) {
      iris_chain_to_new_batch(batch);
   }
}

/**
 * Allocate space in the current command buffer, and return a pointer
 * to the mapped area so the caller can write commands there.
 *
 * This should be called whenever emitting commands.
 */
static inline void *
iris_get_command_space(struct iris_batch *batch, unsigned bytes)
{
   iris_require_command_space(batch, bytes);
   void *map = batch->map_next;
   batch->map_next += bytes;
   return map;
}

/**
 * Helper to emit GPU commands - allocates space, copies them there.
 */
static inline void
iris_batch_emit(struct iris_batch *batch, const void *data, unsigned size)
{
   void *map = iris_get_command_space(batch, size);
   memcpy(map, data, size);
}

/**
 * Get a pointer to the batch's signalling syncpt.  Does not refcount.
 */
static inline struct iris_syncpt *
iris_batch_get_signal_syncpt(struct iris_batch *batch)
{
   /* The signalling syncpt is the first one in the list. */
   struct iris_syncpt *syncpt =
      ((struct iris_syncpt **) util_dynarray_begin(&batch->syncpts))[0];
   return syncpt;
}


/**
 * Take a reference to the batch's signalling syncpt.
 *
 * Callers can use this to wait for the the current batch under construction
 * to complete (after flushing it).
 */
static inline void
iris_batch_reference_signal_syncpt(struct iris_batch *batch,
                                   struct iris_syncpt **out_syncpt)
{
   struct iris_syncpt *syncpt = iris_batch_get_signal_syncpt(batch);
   iris_syncpt_reference(batch->screen, out_syncpt, syncpt);
}

/**
 * Record the size of a piece of state for use in INTEL_DEBUG=bat printing.
 */
static inline void
iris_record_state_size(struct hash_table_u64 *ht,
                       uint32_t offset_from_base,
                       uint32_t size)
{
   if (ht) {
      _mesa_hash_table_u64_insert(ht, offset_from_base,
                                  (void *)(uintptr_t) size);
   }
}

#endif
