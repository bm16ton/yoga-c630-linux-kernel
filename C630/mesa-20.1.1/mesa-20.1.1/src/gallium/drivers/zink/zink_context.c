/*
 * Copyright 2018 Collabora Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "zink_context.h"

#include "zink_batch.h"
#include "zink_compiler.h"
#include "zink_fence.h"
#include "zink_framebuffer.h"
#include "zink_helpers.h"
#include "zink_pipeline.h"
#include "zink_render_pass.h"
#include "zink_resource.h"
#include "zink_screen.h"
#include "zink_state.h"
#include "zink_surface.h"

#include "indices/u_primconvert.h"
#include "util/u_blitter.h"
#include "util/u_debug.h"
#include "util/format/u_format.h"
#include "util/u_framebuffer.h"
#include "util/u_helpers.h"
#include "util/u_inlines.h"

#include "nir.h"

#include "util/u_memory.h"
#include "util/u_upload_mgr.h"

static void
zink_context_destroy(struct pipe_context *pctx)
{
   struct zink_context *ctx = zink_context(pctx);
   struct zink_screen *screen = zink_screen(pctx->screen);

   if (vkQueueWaitIdle(ctx->queue) != VK_SUCCESS)
      debug_printf("vkQueueWaitIdle failed\n");

   for (int i = 0; i < ARRAY_SIZE(ctx->batches); ++i)
      vkFreeCommandBuffers(screen->dev, ctx->cmdpool, 1, &ctx->batches[i].cmdbuf);
   vkDestroyCommandPool(screen->dev, ctx->cmdpool, NULL);

   util_primconvert_destroy(ctx->primconvert);
   u_upload_destroy(pctx->stream_uploader);
   slab_destroy_child(&ctx->transfer_pool);
   util_blitter_destroy(ctx->blitter);
   FREE(ctx);
}

static VkSamplerMipmapMode
sampler_mipmap_mode(enum pipe_tex_mipfilter filter)
{
   switch (filter) {
   case PIPE_TEX_MIPFILTER_NEAREST: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
   case PIPE_TEX_MIPFILTER_LINEAR: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
   case PIPE_TEX_MIPFILTER_NONE:
      unreachable("PIPE_TEX_MIPFILTER_NONE should be dealt with earlier");
   }
   unreachable("unexpected filter");
}

static VkSamplerAddressMode
sampler_address_mode(enum pipe_tex_wrap filter)
{
   switch (filter) {
   case PIPE_TEX_WRAP_REPEAT: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
   case PIPE_TEX_WRAP_CLAMP: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; /* not technically correct, but kinda works */
   case PIPE_TEX_WRAP_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
   case PIPE_TEX_WRAP_CLAMP_TO_BORDER: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
   case PIPE_TEX_WRAP_MIRROR_REPEAT: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
   case PIPE_TEX_WRAP_MIRROR_CLAMP: return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE; /* not technically correct, but kinda works */
   case PIPE_TEX_WRAP_MIRROR_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
   case PIPE_TEX_WRAP_MIRROR_CLAMP_TO_BORDER: return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE; /* not technically correct, but kinda works */
   }
   unreachable("unexpected wrap");
}

static VkCompareOp
compare_op(enum pipe_compare_func op)
{
   switch (op) {
      case PIPE_FUNC_NEVER: return VK_COMPARE_OP_NEVER;
      case PIPE_FUNC_LESS: return VK_COMPARE_OP_LESS;
      case PIPE_FUNC_EQUAL: return VK_COMPARE_OP_EQUAL;
      case PIPE_FUNC_LEQUAL: return VK_COMPARE_OP_LESS_OR_EQUAL;
      case PIPE_FUNC_GREATER: return VK_COMPARE_OP_GREATER;
      case PIPE_FUNC_NOTEQUAL: return VK_COMPARE_OP_NOT_EQUAL;
      case PIPE_FUNC_GEQUAL: return VK_COMPARE_OP_GREATER_OR_EQUAL;
      case PIPE_FUNC_ALWAYS: return VK_COMPARE_OP_ALWAYS;
   }
   unreachable("unexpected compare");
}

static void *
zink_create_sampler_state(struct pipe_context *pctx,
                          const struct pipe_sampler_state *state)
{
   struct zink_screen *screen = zink_screen(pctx->screen);

   VkSamplerCreateInfo sci = {};
   sci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
   sci.magFilter = zink_filter(state->mag_img_filter);
   sci.minFilter = zink_filter(state->min_img_filter);

   if (state->min_mip_filter != PIPE_TEX_MIPFILTER_NONE) {
      sci.mipmapMode = sampler_mipmap_mode(state->min_mip_filter);
      sci.minLod = state->min_lod;
      sci.maxLod = state->max_lod;
   } else {
      sci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
      sci.minLod = 0;
      sci.maxLod = 0;
   }

   sci.addressModeU = sampler_address_mode(state->wrap_s);
   sci.addressModeV = sampler_address_mode(state->wrap_t);
   sci.addressModeW = sampler_address_mode(state->wrap_r);
   sci.mipLodBias = state->lod_bias;

   if (state->compare_mode == PIPE_TEX_COMPARE_NONE)
      sci.compareOp = VK_COMPARE_OP_NEVER;
   else {
      sci.compareOp = compare_op(state->compare_func);
      sci.compareEnable = VK_TRUE;
   }

   sci.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK; // TODO
   sci.unnormalizedCoordinates = !state->normalized_coords;

   if (state->max_anisotropy > 1) {
      sci.maxAnisotropy = state->max_anisotropy;
      sci.anisotropyEnable = VK_TRUE;
   }

   VkSampler *sampler = CALLOC(1, sizeof(VkSampler));
   if (!sampler)
      return NULL;

   if (vkCreateSampler(screen->dev, &sci, NULL, sampler) != VK_SUCCESS) {
      FREE(sampler);
      return NULL;
   }

   return sampler;
}

static void
zink_bind_sampler_states(struct pipe_context *pctx,
                         enum pipe_shader_type shader,
                         unsigned start_slot,
                         unsigned num_samplers,
                         void **samplers)
{
   struct zink_context *ctx = zink_context(pctx);
   for (unsigned i = 0; i < num_samplers; ++i) {
      VkSampler *sampler = samplers[i];
      ctx->sampler_states[shader][start_slot + i] = sampler;
      ctx->samplers[shader][start_slot + i] = sampler ? *sampler : VK_NULL_HANDLE;
   }
   ctx->num_samplers[shader] = start_slot + num_samplers;
}

static void
zink_delete_sampler_state(struct pipe_context *pctx,
                          void *sampler_state)
{
   struct zink_batch *batch = zink_curr_batch(zink_context(pctx));
   util_dynarray_append(&batch->zombie_samplers, VkSampler,
                        *(VkSampler *)sampler_state);
   FREE(sampler_state);
}


static VkImageViewType
image_view_type(enum pipe_texture_target target)
{
   switch (target) {
   case PIPE_TEXTURE_1D: return VK_IMAGE_VIEW_TYPE_1D;
   case PIPE_TEXTURE_1D_ARRAY: return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
   case PIPE_TEXTURE_2D: return VK_IMAGE_VIEW_TYPE_2D;
   case PIPE_TEXTURE_2D_ARRAY: return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
   case PIPE_TEXTURE_CUBE: return VK_IMAGE_VIEW_TYPE_CUBE;
   case PIPE_TEXTURE_CUBE_ARRAY: return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
   case PIPE_TEXTURE_3D: return VK_IMAGE_VIEW_TYPE_3D;
   case PIPE_TEXTURE_RECT: return VK_IMAGE_VIEW_TYPE_2D;
   default:
      unreachable("unexpected target");
   }
}

static VkComponentSwizzle
component_mapping(enum pipe_swizzle swizzle)
{
   switch (swizzle) {
   case PIPE_SWIZZLE_X: return VK_COMPONENT_SWIZZLE_R;
   case PIPE_SWIZZLE_Y: return VK_COMPONENT_SWIZZLE_G;
   case PIPE_SWIZZLE_Z: return VK_COMPONENT_SWIZZLE_B;
   case PIPE_SWIZZLE_W: return VK_COMPONENT_SWIZZLE_A;
   case PIPE_SWIZZLE_0: return VK_COMPONENT_SWIZZLE_ZERO;
   case PIPE_SWIZZLE_1: return VK_COMPONENT_SWIZZLE_ONE;
   case PIPE_SWIZZLE_NONE: return VK_COMPONENT_SWIZZLE_IDENTITY; // ???
   default:
      unreachable("unexpected swizzle");
   }
}

static VkImageAspectFlags
sampler_aspect_from_format(enum pipe_format fmt)
{
   if (util_format_is_depth_or_stencil(fmt)) {
      const struct util_format_description *desc = util_format_description(fmt);
      if (util_format_has_depth(desc))
         return VK_IMAGE_ASPECT_DEPTH_BIT;
      assert(util_format_has_stencil(desc));
      return VK_IMAGE_ASPECT_STENCIL_BIT;
   } else
     return VK_IMAGE_ASPECT_COLOR_BIT;
}

static struct pipe_sampler_view *
zink_create_sampler_view(struct pipe_context *pctx, struct pipe_resource *pres,
                         const struct pipe_sampler_view *state)
{
   struct zink_screen *screen = zink_screen(pctx->screen);
   struct zink_resource *res = zink_resource(pres);
   struct zink_sampler_view *sampler_view = CALLOC_STRUCT(zink_sampler_view);

   sampler_view->base = *state;
   sampler_view->base.texture = NULL;
   pipe_resource_reference(&sampler_view->base.texture, pres);
   sampler_view->base.reference.count = 1;
   sampler_view->base.context = pctx;

   VkImageViewCreateInfo ivci = {};
   ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
   ivci.image = res->image;
   ivci.viewType = image_view_type(state->target);
   ivci.format = zink_get_format(screen, state->format);
   ivci.components.r = component_mapping(state->swizzle_r);
   ivci.components.g = component_mapping(state->swizzle_g);
   ivci.components.b = component_mapping(state->swizzle_b);
   ivci.components.a = component_mapping(state->swizzle_a);

   ivci.subresourceRange.aspectMask = sampler_aspect_from_format(state->format);
   ivci.subresourceRange.baseMipLevel = state->u.tex.first_level;
   ivci.subresourceRange.baseArrayLayer = state->u.tex.first_layer;
   ivci.subresourceRange.levelCount = state->u.tex.last_level - state->u.tex.first_level + 1;
   ivci.subresourceRange.layerCount = state->u.tex.last_layer - state->u.tex.first_layer + 1;

   VkResult err = vkCreateImageView(screen->dev, &ivci, NULL, &sampler_view->image_view);
   if (err != VK_SUCCESS) {
      FREE(sampler_view);
      return NULL;
   }

   return &sampler_view->base;
}

static void
zink_sampler_view_destroy(struct pipe_context *pctx,
                          struct pipe_sampler_view *pview)
{
   struct zink_sampler_view *view = zink_sampler_view(pview);
   vkDestroyImageView(zink_screen(pctx->screen)->dev, view->image_view, NULL);
   FREE(view);
}

static void *
zink_create_vs_state(struct pipe_context *pctx,
                     const struct pipe_shader_state *shader)
{
   struct nir_shader *nir;
   if (shader->type != PIPE_SHADER_IR_NIR)
      nir = zink_tgsi_to_nir(pctx->screen, shader->tokens);
   else
      nir = (struct nir_shader *)shader->ir.nir;

   return zink_compile_nir(zink_screen(pctx->screen), nir);
}

static void
bind_stage(struct zink_context *ctx, enum pipe_shader_type stage,
           struct zink_shader *shader)
{
   assert(stage < PIPE_SHADER_COMPUTE);
   ctx->gfx_stages[stage] = shader;
   ctx->dirty_program = true;
}

static void
zink_bind_vs_state(struct pipe_context *pctx,
                   void *cso)
{
   bind_stage(zink_context(pctx), PIPE_SHADER_VERTEX, cso);
}

static void
zink_delete_vs_state(struct pipe_context *pctx,
                     void *cso)
{
   zink_shader_free(zink_screen(pctx->screen), cso);
}

static void *
zink_create_fs_state(struct pipe_context *pctx,
                     const struct pipe_shader_state *shader)
{
   struct nir_shader *nir;
   if (shader->type != PIPE_SHADER_IR_NIR)
      nir = zink_tgsi_to_nir(pctx->screen, shader->tokens);
   else
      nir = (struct nir_shader *)shader->ir.nir;

   return zink_compile_nir(zink_screen(pctx->screen), nir);
}

static void
zink_bind_fs_state(struct pipe_context *pctx,
                   void *cso)
{
   bind_stage(zink_context(pctx), PIPE_SHADER_FRAGMENT, cso);
}

static void
zink_delete_fs_state(struct pipe_context *pctx,
                     void *cso)
{
   zink_shader_free(zink_screen(pctx->screen), cso);
}

static void
zink_set_polygon_stipple(struct pipe_context *pctx,
                         const struct pipe_poly_stipple *ps)
{
}

static void
zink_set_vertex_buffers(struct pipe_context *pctx,
                        unsigned start_slot,
                        unsigned num_buffers,
                        const struct pipe_vertex_buffer *buffers)
{
   struct zink_context *ctx = zink_context(pctx);

   if (buffers) {
      for (int i = 0; i < num_buffers; ++i) {
         const struct pipe_vertex_buffer *vb = buffers + i;
         ctx->gfx_pipeline_state.bindings[start_slot + i].stride = vb->stride;
      }
   }

   util_set_vertex_buffers_mask(ctx->buffers, &ctx->buffers_enabled_mask,
                                buffers, start_slot, num_buffers);
}

static void
zink_set_viewport_states(struct pipe_context *pctx,
                         unsigned start_slot,
                         unsigned num_viewports,
                         const struct pipe_viewport_state *state)
{
   struct zink_context *ctx = zink_context(pctx);

   for (unsigned i = 0; i < num_viewports; ++i) {
      VkViewport viewport = {
         state[i].translate[0] - state[i].scale[0],
         state[i].translate[1] - state[i].scale[1],
         state[i].scale[0] * 2,
         state[i].scale[1] * 2,
         state[i].translate[2] - state[i].scale[2],
         state[i].translate[2] + state[i].scale[2]
      };
      ctx->viewport_states[start_slot + i] = state[i];
      ctx->viewports[start_slot + i] = viewport;
   }
   ctx->num_viewports = start_slot + num_viewports;
}

static void
zink_set_scissor_states(struct pipe_context *pctx,
                        unsigned start_slot, unsigned num_scissors,
                        const struct pipe_scissor_state *states)
{
   struct zink_context *ctx = zink_context(pctx);

   for (unsigned i = 0; i < num_scissors; i++) {
      VkRect2D scissor;

      scissor.offset.x = states[i].minx;
      scissor.offset.y = states[i].miny;
      scissor.extent.width = states[i].maxx - states[i].minx;
      scissor.extent.height = states[i].maxy - states[i].miny;
      ctx->scissor_states[start_slot + i] = states[i];
      ctx->scissors[start_slot + i] = scissor;
   }
}

static void
zink_set_constant_buffer(struct pipe_context *pctx,
                         enum pipe_shader_type shader, uint index,
                         const struct pipe_constant_buffer *cb)
{
   struct zink_context *ctx = zink_context(pctx);

   if (cb) {
      struct pipe_resource *buffer = cb->buffer;
      unsigned offset = cb->buffer_offset;
      if (cb->user_buffer) {
         struct zink_screen *screen = zink_screen(pctx->screen);
         u_upload_data(ctx->base.const_uploader, 0, cb->buffer_size,
                       screen->props.limits.minUniformBufferOffsetAlignment,
                       cb->user_buffer, &offset, &buffer);
      }

      pipe_resource_reference(&ctx->ubos[shader][index].buffer, buffer);
      ctx->ubos[shader][index].buffer_offset = offset;
      ctx->ubos[shader][index].buffer_size = cb->buffer_size;
      ctx->ubos[shader][index].user_buffer = NULL;

      if (cb->user_buffer)
         pipe_resource_reference(&buffer, NULL);
   } else {
      pipe_resource_reference(&ctx->ubos[shader][index].buffer, NULL);
      ctx->ubos[shader][index].buffer_offset = 0;
      ctx->ubos[shader][index].buffer_size = 0;
      ctx->ubos[shader][index].user_buffer = NULL;
   }
}

static void
zink_set_sampler_views(struct pipe_context *pctx,
                       enum pipe_shader_type shader_type,
                       unsigned start_slot,
                       unsigned num_views,
                       struct pipe_sampler_view **views)
{
   struct zink_context *ctx = zink_context(pctx);
   assert(views);
   for (unsigned i = 0; i < num_views; ++i) {
      pipe_sampler_view_reference(
         &ctx->image_views[shader_type][start_slot + i],
         views[i]);
   }
   ctx->num_image_views[shader_type] = start_slot + num_views;
}

static void
zink_set_stencil_ref(struct pipe_context *pctx,
                     const struct pipe_stencil_ref *ref)
{
   struct zink_context *ctx = zink_context(pctx);
   ctx->stencil_ref = *ref;
}

static void
zink_set_clip_state(struct pipe_context *pctx,
                    const struct pipe_clip_state *pcs)
{
}

static struct zink_render_pass *
get_render_pass(struct zink_context *ctx)
{
   struct zink_screen *screen = zink_screen(ctx->base.screen);
   const struct pipe_framebuffer_state *fb = &ctx->fb_state;
   struct zink_render_pass_state state = { 0 };

   for (int i = 0; i < fb->nr_cbufs; i++) {
      struct pipe_resource *res = fb->cbufs[i]->texture;
      state.rts[i].format = zink_get_format(screen, fb->cbufs[i]->format);
      state.rts[i].samples = res->nr_samples > 0 ? res->nr_samples :
                                                   VK_SAMPLE_COUNT_1_BIT;
   }
   state.num_cbufs = fb->nr_cbufs;

   if (fb->zsbuf) {
      struct zink_resource *zsbuf = zink_resource(fb->zsbuf->texture);
      state.rts[fb->nr_cbufs].format = zsbuf->format;
      state.rts[fb->nr_cbufs].samples = zsbuf->base.nr_samples > 0 ? zsbuf->base.nr_samples : VK_SAMPLE_COUNT_1_BIT;
   }
   state.have_zsbuf = fb->zsbuf != NULL;

   struct hash_entry *entry = _mesa_hash_table_search(ctx->render_pass_cache,
                                                      &state);
   if (!entry) {
      struct zink_render_pass *rp;
      rp = zink_create_render_pass(screen, &state);
      entry = _mesa_hash_table_insert(ctx->render_pass_cache, &state, rp);
      if (!entry)
         return NULL;
   }

   return entry->data;
}

static struct zink_framebuffer *
create_framebuffer(struct zink_context *ctx)
{
   struct zink_screen *screen = zink_screen(ctx->base.screen);

   struct zink_framebuffer_state state = {};
   state.rp = get_render_pass(ctx);
   for (int i = 0; i < ctx->fb_state.nr_cbufs; i++) {
      struct pipe_surface *psurf = ctx->fb_state.cbufs[i];
      state.attachments[i] = zink_surface(psurf);
   }

   state.num_attachments = ctx->fb_state.nr_cbufs;
   if (ctx->fb_state.zsbuf) {
      struct pipe_surface *psurf = ctx->fb_state.zsbuf;
      state.attachments[state.num_attachments++] = zink_surface(psurf);
   }

   state.width = ctx->fb_state.width;
   state.height = ctx->fb_state.height;
   state.layers = MAX2(ctx->fb_state.layers, 1);

   return zink_create_framebuffer(screen, &state);
}

void
zink_begin_render_pass(struct zink_context *ctx, struct zink_batch *batch)
{
   struct zink_screen *screen = zink_screen(ctx->base.screen);
   assert(batch == zink_curr_batch(ctx));
   assert(ctx->gfx_pipeline_state.render_pass);

   struct pipe_framebuffer_state *fb_state = &ctx->fb_state;

   VkRenderPassBeginInfo rpbi = {};
   rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
   rpbi.renderPass = ctx->gfx_pipeline_state.render_pass->render_pass;
   rpbi.renderArea.offset.x = 0;
   rpbi.renderArea.offset.y = 0;
   rpbi.renderArea.extent.width = fb_state->width;
   rpbi.renderArea.extent.height = fb_state->height;
   rpbi.clearValueCount = 0;
   rpbi.pClearValues = NULL;
   rpbi.framebuffer = ctx->framebuffer->fb;

   assert(ctx->gfx_pipeline_state.render_pass && ctx->framebuffer);
   assert(!batch->rp || batch->rp == ctx->gfx_pipeline_state.render_pass);
   assert(!batch->fb || batch->fb == ctx->framebuffer);

   for (int i = 0; i < fb_state->nr_cbufs; i++) {
      struct zink_resource *res = zink_resource(fb_state->cbufs[i]->texture);
      if (res->layout != VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
         zink_resource_barrier(batch->cmdbuf, res, res->aspect,
                               VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
   }

   if (fb_state->zsbuf) {
      struct zink_resource *res = zink_resource(fb_state->zsbuf->texture);
      if (res->layout != VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
         zink_resource_barrier(batch->cmdbuf, res, res->aspect,
                               VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
   }

   zink_render_pass_reference(screen, &batch->rp, ctx->gfx_pipeline_state.render_pass);
   zink_framebuffer_reference(screen, &batch->fb, ctx->framebuffer);

   vkCmdBeginRenderPass(batch->cmdbuf, &rpbi, VK_SUBPASS_CONTENTS_INLINE);
}

static void
flush_batch(struct zink_context *ctx)
{
   struct zink_batch *batch = zink_curr_batch(ctx);
   if (batch->rp)
      vkCmdEndRenderPass(batch->cmdbuf);

   zink_end_batch(ctx, batch);

   ctx->curr_batch++;
   if (ctx->curr_batch == ARRAY_SIZE(ctx->batches))
      ctx->curr_batch = 0;

   zink_start_batch(ctx, zink_curr_batch(ctx));
}

struct zink_batch *
zink_batch_rp(struct zink_context *ctx)
{
   struct zink_batch *batch = zink_curr_batch(ctx);
   if (!batch->rp) {
      zink_begin_render_pass(ctx, batch);
      assert(batch->rp);
   }
   return batch;
}

struct zink_batch *
zink_batch_no_rp(struct zink_context *ctx)
{
   struct zink_batch *batch = zink_curr_batch(ctx);
   if (batch->rp) {
      /* flush batch and get a new one */
      flush_batch(ctx);
      batch = zink_curr_batch(ctx);
      assert(!batch->rp);
   }
   return batch;
}

static void
zink_set_framebuffer_state(struct pipe_context *pctx,
                           const struct pipe_framebuffer_state *state)
{
   struct zink_context *ctx = zink_context(pctx);
   struct zink_screen *screen = zink_screen(pctx->screen);

   VkSampleCountFlagBits rast_samples = VK_SAMPLE_COUNT_1_BIT;
   for (int i = 0; i < state->nr_cbufs; i++)
      rast_samples = MAX2(rast_samples, state->cbufs[i]->texture->nr_samples);
   if (state->zsbuf && state->zsbuf->texture->nr_samples)
      rast_samples = MAX2(rast_samples, state->zsbuf->texture->nr_samples);

   util_copy_framebuffer_state(&ctx->fb_state, state);

   struct zink_framebuffer *fb = ctx->framebuffer;
   /* explicitly unref previous fb to ensure it gets destroyed */
   if (fb)
      zink_framebuffer_reference(screen, &fb, NULL);
   fb = create_framebuffer(ctx);
   zink_framebuffer_reference(screen, &ctx->framebuffer, fb);
   zink_render_pass_reference(screen, &ctx->gfx_pipeline_state.render_pass, fb->rp);

   ctx->gfx_pipeline_state.rast_samples = rast_samples;
   ctx->gfx_pipeline_state.num_attachments = state->nr_cbufs;

   struct zink_batch *batch = zink_batch_no_rp(ctx);

   for (int i = 0; i < state->nr_cbufs; i++) {
      struct zink_resource *res = zink_resource(state->cbufs[i]->texture);
      if (res->layout != VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
         zink_resource_barrier(batch->cmdbuf, res, res->aspect,
                               VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
   }

   if (state->zsbuf) {
      struct zink_resource *res = zink_resource(state->zsbuf->texture);
      if (res->layout != VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
         zink_resource_barrier(batch->cmdbuf, res, res->aspect,
                               VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
   }
}

static void
zink_set_blend_color(struct pipe_context *pctx,
                     const struct pipe_blend_color *color)
{
   struct zink_context *ctx = zink_context(pctx);
   memcpy(ctx->blend_constants, color->color, sizeof(float) * 4);
}

static void
zink_set_sample_mask(struct pipe_context *pctx, unsigned sample_mask)
{
   struct zink_context *ctx = zink_context(pctx);
   ctx->gfx_pipeline_state.sample_mask = sample_mask;
}

static VkAccessFlags
access_src_flags(VkImageLayout layout)
{
   switch (layout) {
   case VK_IMAGE_LAYOUT_UNDEFINED:
   case VK_IMAGE_LAYOUT_GENERAL:
      return 0;

   case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
      return VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
   case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
      return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

   case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
      return VK_ACCESS_SHADER_READ_BIT;

   case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
      return VK_ACCESS_TRANSFER_READ_BIT;

   case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
      return VK_ACCESS_TRANSFER_WRITE_BIT;

   case VK_IMAGE_LAYOUT_PREINITIALIZED:
      return VK_ACCESS_HOST_WRITE_BIT;

   default:
      unreachable("unexpected layout");
   }
}

static VkAccessFlags
access_dst_flags(VkImageLayout layout)
{
   switch (layout) {
   case VK_IMAGE_LAYOUT_UNDEFINED:
   case VK_IMAGE_LAYOUT_GENERAL:
      return 0;

   case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
      return VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
   case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
      return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

   case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
      return VK_ACCESS_TRANSFER_READ_BIT;

   case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
      return VK_ACCESS_TRANSFER_WRITE_BIT;

   default:
      unreachable("unexpected layout");
   }
}

static VkPipelineStageFlags
pipeline_dst_stage(VkImageLayout layout)
{
   switch (layout) {
   case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
      return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
   case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
      return VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;

   case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
      return VK_PIPELINE_STAGE_TRANSFER_BIT;
   case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
      return VK_PIPELINE_STAGE_TRANSFER_BIT;

   default:
      return VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
   }
}

static VkPipelineStageFlags
pipeline_src_stage(VkImageLayout layout)
{
   switch (layout) {
   case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
      return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
   case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
      return VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

   case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
      return VK_PIPELINE_STAGE_TRANSFER_BIT;
   case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
      return VK_PIPELINE_STAGE_TRANSFER_BIT;

   default:
      return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
   }
}


void
zink_resource_barrier(VkCommandBuffer cmdbuf, struct zink_resource *res,
                      VkImageAspectFlags aspect, VkImageLayout new_layout)
{
   VkImageSubresourceRange isr = {
      aspect,
      0, VK_REMAINING_MIP_LEVELS,
      0, VK_REMAINING_ARRAY_LAYERS
   };

   VkImageMemoryBarrier imb = {
      VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      NULL,
      access_src_flags(res->layout),
      access_dst_flags(new_layout),
      res->layout,
      new_layout,
      VK_QUEUE_FAMILY_IGNORED,
      VK_QUEUE_FAMILY_IGNORED,
      res->image,
      isr
   };
   vkCmdPipelineBarrier(
      cmdbuf,
      pipeline_src_stage(res->layout),
      pipeline_dst_stage(new_layout),
      0,
      0, NULL,
      0, NULL,
      1, &imb
   );

   res->layout = new_layout;
}

static void
zink_clear(struct pipe_context *pctx,
           unsigned buffers,
           const struct pipe_scissor_state *scissor_state,
           const union pipe_color_union *pcolor,
           double depth, unsigned stencil)
{
   struct zink_context *ctx = zink_context(pctx);
   struct pipe_framebuffer_state *fb = &ctx->fb_state;

   /* FIXME: this is very inefficient; if no renderpass has been started yet,
    * we should record the clear if it's full-screen, and apply it as we
    * start the render-pass. Otherwise we can do a partial out-of-renderpass
    * clear.
    */
   struct zink_batch *batch = zink_batch_rp(ctx);

   VkClearAttachment attachments[1 + PIPE_MAX_COLOR_BUFS];
   int num_attachments = 0;

   if (buffers & PIPE_CLEAR_COLOR) {
      VkClearColorValue color;
      color.float32[0] = pcolor->f[0];
      color.float32[1] = pcolor->f[1];
      color.float32[2] = pcolor->f[2];
      color.float32[3] = pcolor->f[3];

      for (unsigned i = 0; i < fb->nr_cbufs; i++) {
         if (!(buffers & (PIPE_CLEAR_COLOR0 << i)) || !fb->cbufs[i])
            continue;

         attachments[num_attachments].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
         attachments[num_attachments].colorAttachment = i;
         attachments[num_attachments].clearValue.color = color;
         ++num_attachments;
      }
   }

   if (buffers & PIPE_CLEAR_DEPTHSTENCIL && fb->zsbuf) {
      VkImageAspectFlags aspect = 0;
      if (buffers & PIPE_CLEAR_DEPTH)
         aspect |= VK_IMAGE_ASPECT_DEPTH_BIT;
      if (buffers & PIPE_CLEAR_STENCIL)
         aspect |= VK_IMAGE_ASPECT_STENCIL_BIT;

      attachments[num_attachments].aspectMask = aspect;
      attachments[num_attachments].clearValue.depthStencil.depth = depth;
      attachments[num_attachments].clearValue.depthStencil.stencil = stencil;
      ++num_attachments;
   }

   VkClearRect cr;
   cr.rect.offset.x = 0;
   cr.rect.offset.y = 0;
   cr.rect.extent.width = fb->width;
   cr.rect.extent.height = fb->height;
   cr.baseArrayLayer = 0;
   cr.layerCount = util_framebuffer_get_num_layers(fb);
   vkCmdClearAttachments(batch->cmdbuf, num_attachments, attachments, 1, &cr);
}

VkShaderStageFlagBits
zink_shader_stage(enum pipe_shader_type type)
{
   VkShaderStageFlagBits stages[] = {
      [PIPE_SHADER_VERTEX] = VK_SHADER_STAGE_VERTEX_BIT,
      [PIPE_SHADER_FRAGMENT] = VK_SHADER_STAGE_FRAGMENT_BIT,
      [PIPE_SHADER_GEOMETRY] = VK_SHADER_STAGE_GEOMETRY_BIT,
      [PIPE_SHADER_TESS_CTRL] = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
      [PIPE_SHADER_TESS_EVAL] = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
      [PIPE_SHADER_COMPUTE] = VK_SHADER_STAGE_COMPUTE_BIT,
   };
   return stages[type];
}

static uint32_t
hash_gfx_program(const void *key)
{
   return _mesa_hash_data(key, sizeof(struct zink_shader *) * (PIPE_SHADER_TYPES - 1));
}

static bool
equals_gfx_program(const void *a, const void *b)
{
   return memcmp(a, b, sizeof(struct zink_shader *) * (PIPE_SHADER_TYPES - 1)) == 0;
}

static uint32_t
hash_render_pass_state(const void *key)
{
   return _mesa_hash_data(key, sizeof(struct zink_render_pass_state));
}

static bool
equals_render_pass_state(const void *a, const void *b)
{
   return memcmp(a, b, sizeof(struct zink_render_pass_state)) == 0;
}

static void
zink_flush(struct pipe_context *pctx,
           struct pipe_fence_handle **pfence,
           enum pipe_flush_flags flags)
{
   struct zink_context *ctx = zink_context(pctx);

   struct zink_batch *batch = zink_curr_batch(ctx);
   flush_batch(ctx);

   if (pfence)
      zink_fence_reference(zink_screen(pctx->screen),
                           (struct zink_fence **)pfence,
                           batch->fence);

   /* HACK:
    * For some strange reason, we need to finish before presenting, or else
    * we start rendering on top of the back-buffer for the next frame. This
    * seems like a bug in the DRI-driver to me, because we really should
    * be properly protected by fences here, and the back-buffer should
    * either be swapped with the front-buffer, or blitted from. But for
    * some strange reason, neither of these things happen.
    */
   if (flags & PIPE_FLUSH_END_OF_FRAME)
      pctx->screen->fence_finish(pctx->screen, pctx,
                                 (struct pipe_fence_handle *)batch->fence,
                                 PIPE_TIMEOUT_INFINITE);
}

static void
zink_flush_resource(struct pipe_context *pipe,
                    struct pipe_resource *resource)
{
}

static void
zink_resource_copy_region(struct pipe_context *pctx,
                          struct pipe_resource *pdst,
                          unsigned dst_level, unsigned dstx, unsigned dsty, unsigned dstz,
                          struct pipe_resource *psrc,
                          unsigned src_level, const struct pipe_box *src_box)
{
   struct zink_resource *dst = zink_resource(pdst);
   struct zink_resource *src = zink_resource(psrc);
   struct zink_context *ctx = zink_context(pctx);
   if (dst->base.target != PIPE_BUFFER && src->base.target != PIPE_BUFFER) {
      VkImageCopy region = {};

      region.srcSubresource.aspectMask = src->aspect;
      region.srcSubresource.mipLevel = src_level;
      region.srcSubresource.layerCount = 1;
      if (src->base.array_size > 1) {
         region.srcSubresource.baseArrayLayer = src_box->z;
         region.srcSubresource.layerCount = src_box->depth;
         region.extent.depth = 1;
      } else {
         region.srcOffset.z = src_box->z;
         region.srcSubresource.layerCount = 1;
         region.extent.depth = src_box->depth;
      }

      region.srcOffset.x = src_box->x;
      region.srcOffset.y = src_box->y;

      region.dstSubresource.aspectMask = dst->aspect;
      region.dstSubresource.mipLevel = dst_level;
      if (dst->base.array_size > 1) {
         region.dstSubresource.baseArrayLayer = dstz;
         region.dstSubresource.layerCount = src_box->depth;
      } else {
         region.dstOffset.z = dstz;
         region.dstSubresource.layerCount = 1;
      }

      region.dstOffset.x = dstx;
      region.dstOffset.y = dsty;
      region.extent.width = src_box->width;
      region.extent.height = src_box->height;

      struct zink_batch *batch = zink_batch_no_rp(ctx);
      zink_batch_reference_resoure(batch, src);
      zink_batch_reference_resoure(batch, dst);

      if (src->layout != VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
         zink_resource_barrier(batch->cmdbuf, src, src->aspect,
                               VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
      }

      if (dst->layout != VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
         zink_resource_barrier(batch->cmdbuf, dst, dst->aspect,
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
      }

      vkCmdCopyImage(batch->cmdbuf, src->image, src->layout,
                     dst->image, dst->layout,
                     1, &region);
   } else if (dst->base.target == PIPE_BUFFER &&
              src->base.target == PIPE_BUFFER) {
      VkBufferCopy region;
      region.srcOffset = src_box->x;
      region.dstOffset = dstx;
      region.size = src_box->width;

      struct zink_batch *batch = zink_batch_no_rp(ctx);
      zink_batch_reference_resoure(batch, src);
      zink_batch_reference_resoure(batch, dst);

      vkCmdCopyBuffer(batch->cmdbuf, src->buffer, dst->buffer, 1, &region);
   } else
      debug_printf("zink: TODO resource copy\n");
}

struct pipe_context *
zink_context_create(struct pipe_screen *pscreen, void *priv, unsigned flags)
{
   struct zink_screen *screen = zink_screen(pscreen);
   struct zink_context *ctx = CALLOC_STRUCT(zink_context);
   if (!ctx)
      goto fail;

   ctx->base.screen = pscreen;
   ctx->base.priv = priv;

   ctx->base.destroy = zink_context_destroy;

   zink_context_state_init(&ctx->base);

   ctx->base.create_sampler_state = zink_create_sampler_state;
   ctx->base.bind_sampler_states = zink_bind_sampler_states;
   ctx->base.delete_sampler_state = zink_delete_sampler_state;

   ctx->base.create_sampler_view = zink_create_sampler_view;
   ctx->base.set_sampler_views = zink_set_sampler_views;
   ctx->base.sampler_view_destroy = zink_sampler_view_destroy;

   ctx->base.create_vs_state = zink_create_vs_state;
   ctx->base.bind_vs_state = zink_bind_vs_state;
   ctx->base.delete_vs_state = zink_delete_vs_state;

   ctx->base.create_fs_state = zink_create_fs_state;
   ctx->base.bind_fs_state = zink_bind_fs_state;
   ctx->base.delete_fs_state = zink_delete_fs_state;

   ctx->base.set_polygon_stipple = zink_set_polygon_stipple;
   ctx->base.set_vertex_buffers = zink_set_vertex_buffers;
   ctx->base.set_viewport_states = zink_set_viewport_states;
   ctx->base.set_scissor_states = zink_set_scissor_states;
   ctx->base.set_constant_buffer = zink_set_constant_buffer;
   ctx->base.set_framebuffer_state = zink_set_framebuffer_state;
   ctx->base.set_stencil_ref = zink_set_stencil_ref;
   ctx->base.set_clip_state = zink_set_clip_state;
   ctx->base.set_blend_color = zink_set_blend_color;

   ctx->base.set_sample_mask = zink_set_sample_mask;

   ctx->base.clear = zink_clear;
   ctx->base.draw_vbo = zink_draw_vbo;
   ctx->base.flush = zink_flush;

   ctx->base.resource_copy_region = zink_resource_copy_region;
   ctx->base.blit = zink_blit;

   ctx->base.flush_resource = zink_flush_resource;
   zink_context_surface_init(&ctx->base);
   zink_context_resource_init(&ctx->base);
   zink_context_query_init(&ctx->base);

   slab_create_child(&ctx->transfer_pool, &screen->transfer_pool);

   ctx->base.stream_uploader = u_upload_create_default(&ctx->base);
   ctx->base.const_uploader = ctx->base.stream_uploader;

   int prim_hwsupport = 1 << PIPE_PRIM_POINTS |
                        1 << PIPE_PRIM_LINES |
                        1 << PIPE_PRIM_LINE_STRIP |
                        1 << PIPE_PRIM_TRIANGLES |
                        1 << PIPE_PRIM_TRIANGLE_STRIP |
                        1 << PIPE_PRIM_TRIANGLE_FAN;

   ctx->primconvert = util_primconvert_create(&ctx->base, prim_hwsupport);
   if (!ctx->primconvert)
      goto fail;

   ctx->blitter = util_blitter_create(&ctx->base);
   if (!ctx->blitter)
      goto fail;

   VkCommandPoolCreateInfo cpci = {};
   cpci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
   cpci.queueFamilyIndex = screen->gfx_queue;
   cpci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
   if (vkCreateCommandPool(screen->dev, &cpci, NULL, &ctx->cmdpool) != VK_SUCCESS)
      goto fail;

   VkCommandBufferAllocateInfo cbai = {};
   cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
   cbai.commandPool = ctx->cmdpool;
   cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
   cbai.commandBufferCount = 1;

   VkDescriptorPoolSize sizes[] = {
      {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         ZINK_BATCH_DESC_SIZE},
      {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ZINK_BATCH_DESC_SIZE}
   };
   VkDescriptorPoolCreateInfo dpci = {};
   dpci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
   dpci.pPoolSizes = sizes;
   dpci.poolSizeCount = ARRAY_SIZE(sizes);
   dpci.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
   dpci.maxSets = ZINK_BATCH_DESC_SIZE;

   for (int i = 0; i < ARRAY_SIZE(ctx->batches); ++i) {
      if (vkAllocateCommandBuffers(screen->dev, &cbai, &ctx->batches[i].cmdbuf) != VK_SUCCESS)
         goto fail;

      ctx->batches[i].resources = _mesa_set_create(NULL, _mesa_hash_pointer,
                                                   _mesa_key_pointer_equal);
      ctx->batches[i].sampler_views = _mesa_set_create(NULL,
                                                       _mesa_hash_pointer,
                                                       _mesa_key_pointer_equal);

      if (!ctx->batches[i].resources || !ctx->batches[i].sampler_views)
         goto fail;

      util_dynarray_init(&ctx->batches[i].zombie_samplers, NULL);

      if (vkCreateDescriptorPool(screen->dev, &dpci, 0,
                                 &ctx->batches[i].descpool) != VK_SUCCESS)
         goto fail;
   }

   vkGetDeviceQueue(screen->dev, screen->gfx_queue, 0, &ctx->queue);

   ctx->program_cache = _mesa_hash_table_create(NULL,
                                                hash_gfx_program,
                                                equals_gfx_program);
   ctx->render_pass_cache = _mesa_hash_table_create(NULL,
                                                    hash_render_pass_state,
                                                    equals_render_pass_state);
   if (!ctx->program_cache || !ctx->render_pass_cache)
      goto fail;

   const uint8_t data[] = { 0 };
   ctx->dummy_buffer = pipe_buffer_create_with_data(&ctx->base,
      PIPE_BIND_VERTEX_BUFFER, PIPE_USAGE_IMMUTABLE, sizeof(data), data);
   if (!ctx->dummy_buffer)
      goto fail;

   ctx->dirty_program = true;

   /* start the first batch */
   zink_start_batch(ctx, zink_curr_batch(ctx));

   return &ctx->base;

fail:
   if (ctx) {
      vkDestroyCommandPool(screen->dev, ctx->cmdpool, NULL);
      FREE(ctx);
   }
   return NULL;
}
