#include "zink_context.h"
#include "zink_helpers.h"
#include "zink_resource.h"
#include "zink_screen.h"

#include "util/u_blitter.h"
#include "util/format/u_format.h"

static bool
blit_resolve(struct zink_context *ctx, const struct pipe_blit_info *info)
{
   if (util_format_get_mask(info->dst.format) != info->mask ||
       util_format_get_mask(info->src.format) != info->mask ||
       info->scissor_enable ||
       info->alpha_blend)
      return false;

   struct zink_resource *src = zink_resource(info->src.resource);
   struct zink_resource *dst = zink_resource(info->dst.resource);

   struct zink_screen *screen = zink_screen(ctx->base.screen);
   if (src->format != zink_get_format(screen, info->src.format) ||
       dst->format != zink_get_format(screen, info->dst.format))
      return false;

   struct zink_batch *batch = zink_batch_no_rp(ctx);

   zink_batch_reference_resoure(batch, src);
   zink_batch_reference_resoure(batch, dst);

   if (src->layout != VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
      zink_resource_barrier(batch->cmdbuf, src, src->aspect,
                            VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

   if (dst->layout != VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
      zink_resource_barrier(batch->cmdbuf, dst, dst->aspect,
                            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

   VkImageResolve region = {};

   region.srcSubresource.aspectMask = src->aspect;
   region.srcSubresource.mipLevel = info->src.level;
   region.srcSubresource.baseArrayLayer = 0; // no clue
   region.srcSubresource.layerCount = 1; // no clue
   region.srcOffset.x = info->src.box.x;
   region.srcOffset.y = info->src.box.y;
   region.srcOffset.z = info->src.box.z;

   region.dstSubresource.aspectMask = dst->aspect;
   region.dstSubresource.mipLevel = info->dst.level;
   region.dstSubresource.baseArrayLayer = 0; // no clue
   region.dstSubresource.layerCount = 1; // no clue
   region.dstOffset.x = info->dst.box.x;
   region.dstOffset.y = info->dst.box.y;
   region.dstOffset.z = info->dst.box.z;

   region.extent.width = info->dst.box.width;
   region.extent.height = info->dst.box.height;
   region.extent.depth = info->dst.box.depth;
   vkCmdResolveImage(batch->cmdbuf, src->image, src->layout,
                     dst->image, dst->layout,
                     1, &region);

   return true;
}

static bool
blit_native(struct zink_context *ctx, const struct pipe_blit_info *info)
{
   if (util_format_get_mask(info->dst.format) != info->mask ||
       util_format_get_mask(info->src.format) != info->mask ||
       info->scissor_enable ||
       info->alpha_blend)
      return false;

   if (util_format_is_depth_or_stencil(info->dst.format) &&
       info->dst.format != info->src.format)
      return false;

   struct zink_resource *src = zink_resource(info->src.resource);
   struct zink_resource *dst = zink_resource(info->dst.resource);

   struct zink_screen *screen = zink_screen(ctx->base.screen);
   if (src->format != zink_get_format(screen, info->src.format) ||
       dst->format != zink_get_format(screen, info->dst.format))
      return false;

   struct zink_batch *batch = zink_batch_no_rp(ctx);
   zink_batch_reference_resoure(batch, src);
   zink_batch_reference_resoure(batch, dst);

   if (src == dst) {
      /* The Vulkan 1.1 specification says the following about valid usage
       * of vkCmdBlitImage:
       *
       * "srcImageLayout must be VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
       *  VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL or VK_IMAGE_LAYOUT_GENERAL"
       *
       * and:
       *
       * "dstImageLayout must be VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
       *  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL or VK_IMAGE_LAYOUT_GENERAL"
       *
       * Since we cant have the same image in two states at the same time,
       * we're effectively left with VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR or
       * VK_IMAGE_LAYOUT_GENERAL. And since this isn't a present-related
       * operation, VK_IMAGE_LAYOUT_GENERAL seems most appropriate.
       */
      if (src->layout != VK_IMAGE_LAYOUT_GENERAL)
         zink_resource_barrier(batch->cmdbuf, src, src->aspect,
                               VK_IMAGE_LAYOUT_GENERAL);
   } else {
      if (src->layout != VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
         zink_resource_barrier(batch->cmdbuf, src, src->aspect,
                               VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

      if (dst->layout != VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
         zink_resource_barrier(batch->cmdbuf, dst, dst->aspect,
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
   }

   VkImageBlit region = {};
   region.srcSubresource.aspectMask = src->aspect;
   region.srcSubresource.mipLevel = info->src.level;
   region.srcOffsets[0].x = info->src.box.x;
   region.srcOffsets[0].y = info->src.box.y;
   region.srcOffsets[1].x = info->src.box.x + info->src.box.width;
   region.srcOffsets[1].y = info->src.box.y + info->src.box.height;

   if (src->base.array_size > 1) {
      region.srcOffsets[0].z = 0;
      region.srcOffsets[1].z = 1;
      region.srcSubresource.baseArrayLayer = info->src.box.z;
      region.srcSubresource.layerCount = info->src.box.depth;
   } else {
      region.srcOffsets[0].z = info->src.box.z;
      region.srcOffsets[1].z = info->src.box.z + info->src.box.depth;
      region.srcSubresource.baseArrayLayer = 0;
      region.srcSubresource.layerCount = 1;
   }

   region.dstSubresource.aspectMask = dst->aspect;
   region.dstSubresource.mipLevel = info->dst.level;
   region.dstOffsets[0].x = info->dst.box.x;
   region.dstOffsets[0].y = info->dst.box.y;
   region.dstOffsets[1].x = info->dst.box.x + info->dst.box.width;
   region.dstOffsets[1].y = info->dst.box.y + info->dst.box.height;

   if (dst->base.array_size > 1) {
      region.dstOffsets[0].z = 0;
      region.dstOffsets[1].z = 1;
      region.dstSubresource.baseArrayLayer = info->dst.box.z;
      region.dstSubresource.layerCount = info->dst.box.depth;
   } else {
      region.dstOffsets[0].z = info->dst.box.z;
      region.dstOffsets[1].z = info->dst.box.z + info->dst.box.depth;
      region.dstSubresource.baseArrayLayer = 0;
      region.dstSubresource.layerCount = 1;
   }

   vkCmdBlitImage(batch->cmdbuf, src->image, src->layout,
                  dst->image, dst->layout,
                  1, &region,
                  zink_filter(info->filter));

   return true;
}

void
zink_blit(struct pipe_context *pctx,
          const struct pipe_blit_info *info)
{
   struct zink_context *ctx = zink_context(pctx);
   if (info->src.resource->nr_samples > 1 &&
       info->dst.resource->nr_samples <= 1) {
      if (blit_resolve(ctx, info))
         return;
   } else {
      if (blit_native(ctx, info))
         return;
   }

   if (!util_blitter_is_blit_supported(ctx->blitter, info)) {
      debug_printf("blit unsupported %s -> %s\n",
              util_format_short_name(info->src.resource->format),
              util_format_short_name(info->dst.resource->format));
      return;
   }

   util_blitter_save_blend(ctx->blitter, ctx->gfx_pipeline_state.blend_state);
   util_blitter_save_depth_stencil_alpha(ctx->blitter, ctx->gfx_pipeline_state.depth_stencil_alpha_state);
   util_blitter_save_vertex_elements(ctx->blitter, ctx->element_state);
   util_blitter_save_stencil_ref(ctx->blitter, &ctx->stencil_ref);
   util_blitter_save_rasterizer(ctx->blitter, ctx->rast_state);
   util_blitter_save_fragment_shader(ctx->blitter, ctx->gfx_stages[PIPE_SHADER_FRAGMENT]);
   util_blitter_save_vertex_shader(ctx->blitter, ctx->gfx_stages[PIPE_SHADER_VERTEX]);
   util_blitter_save_framebuffer(ctx->blitter, &ctx->fb_state);
   util_blitter_save_viewport(ctx->blitter, ctx->viewport_states);
   util_blitter_save_scissor(ctx->blitter, ctx->scissor_states);
   util_blitter_save_fragment_sampler_states(ctx->blitter,
                                             ctx->num_samplers[PIPE_SHADER_FRAGMENT],
                                             ctx->sampler_states[PIPE_SHADER_FRAGMENT]);
   util_blitter_save_fragment_sampler_views(ctx->blitter,
                                            ctx->num_image_views[PIPE_SHADER_FRAGMENT],
                                            ctx->image_views[PIPE_SHADER_FRAGMENT]);
   util_blitter_save_fragment_constant_buffer_slot(ctx->blitter, ctx->ubos[PIPE_SHADER_FRAGMENT]);
   util_blitter_save_vertex_buffer_slot(ctx->blitter, ctx->buffers);
   util_blitter_save_sample_mask(ctx->blitter, ctx->gfx_pipeline_state.sample_mask);

   util_blitter_blit(ctx->blitter, info);
}
