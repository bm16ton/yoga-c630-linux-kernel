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
 */

#include "pan_context.h"
#include "pan_job.h"
#include "pan_allocate.h"
#include "panfrost-quirks.h"
#include "util/bitset.h"

/*
 * Within a batch (panfrost_job), there are various types of Mali jobs:
 *
 *  - WRITE_VALUE: generic write primitive, used to zero tiler field
 *  - VERTEX: runs a vertex shader
 *  - TILER: runs tiling and sets up a fragment shader
 *  - FRAGMENT: runs fragment shaders and writes out
 *  - COMPUTE: runs a compute shader
 *  - FUSED: vertex+tiler fused together, implicit intradependency (Bifrost)
 *  - GEOMETRY: runs a geometry shader (unimplemented)
 *  - CACHE_FLUSH: unseen in the wild, theoretically cache flush
 *
 * In between a full batch and a single Mali job is the "job chain", a series
 * of Mali jobs together forming a linked list. Within the job chain, each Mali
 * job can set (up to) two dependencies on other earlier jobs in the chain.
 * This dependency graph forms a scoreboard. The general idea of a scoreboard
 * applies: when there is a data dependency of job B on job A, job B sets one
 * of its dependency indices to job A, ensuring that job B won't start until
 * job A finishes.
 *
 * More specifically, here are a set of rules:
 *
 * - A write value job must appear if and only if there is at least one tiler
 *   job, and tiler jobs must depend on it.
 *
 * - Vertex jobs and tiler jobs are independent.
 *
 * - A tiler job must have a dependency on its data source. If it's getting
 *   data from a vertex job, it depends on the vertex job. If it's getting data
 *   from software, this is null.
 *
 * - Tiler jobs must depend on the write value job (chained or otherwise).
 *
 * - Tiler jobs must be strictly ordered. So each tiler job must depend on the
 *   previous job in the chain.
 *
 * - Jobs linking via next_job has no bearing on order of execution, rather it
 *   just establishes the linked list of jobs, EXCEPT:
 *
 * - A job's dependencies must appear earlier in the linked list (job chain).
 *
 * Justification for each rule:
 *
 * - Write value jobs are used to write a zero into a magic tiling field, which
 *   enables tiling to work. If tiling occurs, they are needed; if it does not,
 *   we cannot emit them since then tiling partially occurs and it's bad.
 *
 * - The hardware has no notion of a "vertex/tiler job" (at least not our
 *   hardware -- other revs have fused jobs, but --- crap, this just got even
 *   more complicated). They are independent units that take in data, process
 *   it, and spit out data.
 *
 * - Any job must depend on its data source, in fact, or risk a
 *   read-before-write hazard. Tiler jobs get their data from vertex jobs, ergo
 *   tiler jobs depend on the corresponding vertex job (if it's there).
 *
 * - The tiler is not thread-safe; this dependency prevents race conditions
 *   between two different jobs trying to write to the tiler outputs at the
 *   same time.
 *
 * - Internally, jobs are scoreboarded; the next job fields just form a linked
 *   list to allow the jobs to be read in; the execution order is from
 *   resolving the dependency fields instead.
 *
 * - The hardware cannot set a dependency on a job it doesn't know about yet,
 *   and dependencies are processed in-order of the next job fields.
 *
 */

/* Generates, uploads, and queues a a new job. All fields are written in order
 * except for next_job accounting (TODO: Should we be clever and defer the
 * upload of the header here until next job to keep the access pattern totally
 * linear? Or is that just a micro op at this point?). Returns the generated
 * index for dep management.
 *
 * Inject is used to inject a job at the front, for wallpapering. If you are
 * not wallpapering and set this, dragons will eat you. */

unsigned
panfrost_new_job(
                struct panfrost_batch *batch,
                enum mali_job_type type,
                bool barrier,
                unsigned local_dep,
                void *payload, size_t payload_size,
                bool inject)
{
        struct panfrost_device *dev = pan_device(batch->ctx->base.screen);

        unsigned global_dep = 0;

        if (type == JOB_TYPE_TILER) {
                /* Tiler jobs must be chained, and on Midgard, the first tiler
                 * job must depend on the write value job, whose index we
                 * reserve now */

                if (batch->tiler_dep)
                        global_dep = batch->tiler_dep;
                else if (!(dev->quirks & IS_BIFROST)) {
                        batch->write_value_index = ++batch->job_index;
                        global_dep = batch->write_value_index;
                }
        }

        /* Assign the index */
        unsigned index = ++batch->job_index;

        struct mali_job_descriptor_header job = {
                .job_descriptor_size = 1,
                .job_type = type,
                .job_barrier = barrier,
                .job_index = index,
                .job_dependency_index_1 = local_dep,
                .job_dependency_index_2 = global_dep,
        };

        if (inject)
                job.next_job = batch->first_job;

        struct panfrost_transfer transfer = panfrost_allocate_transient(batch, sizeof(job) + payload_size);
        memcpy(transfer.cpu, &job, sizeof(job));
        memcpy(transfer.cpu + sizeof(job), payload, payload_size);

        if (inject) {
                batch->first_job = transfer.gpu;
                return index;
        }

        /* Form a chain */
        if (type == JOB_TYPE_TILER)
                batch->tiler_dep = index;

        if (batch->prev_job)
                batch->prev_job->next_job = transfer.gpu;
        else
                batch->first_job = transfer.gpu;

        batch->prev_job = (struct mali_job_descriptor_header *) transfer.cpu;
        return index;
}

/* Generates a write value job, used to initialize the tiler structures. Note
 * this is called right before frame submission. */

void
panfrost_scoreboard_initialize_tiler(struct panfrost_batch *batch)
{
        struct panfrost_device *dev = pan_device(batch->ctx->base.screen);

        /* Check if we even need tiling */
        if (dev->quirks & IS_BIFROST || !batch->tiler_dep)
                return;

        /* Okay, we do. Let's generate it. We'll need the job's polygon list
         * regardless of size. */

        mali_ptr polygon_list = panfrost_batch_get_polygon_list(batch,
                MALI_TILER_MINIMUM_HEADER_SIZE);

        struct mali_job_descriptor_header job = {
                .job_type = JOB_TYPE_WRITE_VALUE,
                .job_index = batch->write_value_index,
                .job_descriptor_size = 1,
                .next_job = batch->first_job
        };

        struct mali_payload_write_value payload = {
                .address = polygon_list,
                .value_descriptor = MALI_WRITE_VALUE_ZERO,
        };

        struct panfrost_transfer transfer = panfrost_allocate_transient(batch, sizeof(job) + sizeof(payload));
        memcpy(transfer.cpu, &job, sizeof(job));
        memcpy(transfer.cpu + sizeof(job), &payload, sizeof(payload));

        batch->first_job = transfer.gpu;
}
