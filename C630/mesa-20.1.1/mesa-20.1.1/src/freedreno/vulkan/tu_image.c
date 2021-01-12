/*
 * Copyright © 2016 Red Hat.
 * Copyright © 2016 Bas Nieuwenhuizen
 *
 * based in part on anv driver which is:
 * Copyright © 2015 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "tu_private.h"

#include "util/debug.h"
#include "util/u_atomic.h"
#include "util/format/u_format.h"
#include "vk_format.h"
#include "vk_util.h"
#include "drm-uapi/drm_fourcc.h"

#include "tu_cs.h"

VkResult
tu_image_create(VkDevice _device,
                const VkImageCreateInfo *pCreateInfo,
                const VkAllocationCallbacks *alloc,
                VkImage *pImage,
                uint64_t modifier)
{
   TU_FROM_HANDLE(tu_device, device, _device);
   struct tu_image *image = NULL;
   assert(pCreateInfo->sType == VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO);

   tu_assert(pCreateInfo->mipLevels > 0);
   tu_assert(pCreateInfo->arrayLayers > 0);
   tu_assert(pCreateInfo->samples > 0);
   tu_assert(pCreateInfo->extent.width > 0);
   tu_assert(pCreateInfo->extent.height > 0);
   tu_assert(pCreateInfo->extent.depth > 0);

   image = vk_zalloc2(&device->alloc, alloc, sizeof(*image), 8,
                      VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
   if (!image)
      return vk_error(device->instance, VK_ERROR_OUT_OF_HOST_MEMORY);

   image->type = pCreateInfo->imageType;

   image->vk_format = pCreateInfo->format;
   image->tiling = pCreateInfo->tiling;
   image->usage = pCreateInfo->usage;
   image->flags = pCreateInfo->flags;
   image->extent = pCreateInfo->extent;
   image->level_count = pCreateInfo->mipLevels;
   image->layer_count = pCreateInfo->arrayLayers;
   image->samples = pCreateInfo->samples;

   image->exclusive = pCreateInfo->sharingMode == VK_SHARING_MODE_EXCLUSIVE;
   if (pCreateInfo->sharingMode == VK_SHARING_MODE_CONCURRENT) {
      for (uint32_t i = 0; i < pCreateInfo->queueFamilyIndexCount; ++i)
         if (pCreateInfo->pQueueFamilyIndices[i] ==
             VK_QUEUE_FAMILY_EXTERNAL)
            image->queue_family_mask |= (1u << TU_MAX_QUEUE_FAMILIES) - 1u;
         else
            image->queue_family_mask |=
               1u << pCreateInfo->pQueueFamilyIndices[i];
   }

   image->shareable =
      vk_find_struct_const(pCreateInfo->pNext,
                           EXTERNAL_MEMORY_IMAGE_CREATE_INFO) != NULL;

   image->layout.tile_mode = TILE6_3;
   bool ubwc_enabled = true;

   /* disable tiling when linear is requested and for compressed formats */
   if (pCreateInfo->tiling == VK_IMAGE_TILING_LINEAR ||
       modifier == DRM_FORMAT_MOD_LINEAR ||
       vk_format_is_compressed(image->vk_format)) {
      image->layout.tile_mode = TILE6_LINEAR;
      ubwc_enabled = false;
   }

   /* UBWC can't be used with E5B9G9R9 */
   if (image->vk_format == VK_FORMAT_E5B9G9R9_UFLOAT_PACK32)
      ubwc_enabled = false;

   /* separate stencil doesn't have a UBWC enable bit */
   if (image->vk_format == VK_FORMAT_S8_UINT)
      ubwc_enabled = false;

   if (image->extent.depth > 1) {
      tu_finishme("UBWC with 3D textures");
      ubwc_enabled = false;
   }

   /* Disable UBWC for storage images.
    *
    * The closed GL driver skips UBWC for storage images (and additionally
    * uses linear for writeonly images).  We seem to have image tiling working
    * in freedreno in general, so turnip matches that.  freedreno also enables
    * UBWC on images, but it's not really tested due to the lack of
    * UBWC-enabled mipmaps in freedreno currently.  Just match the closed GL
    * behavior of no UBWC.
   */
   if (image->usage & VK_IMAGE_USAGE_STORAGE_BIT)
      ubwc_enabled = false;

   uint32_t ubwc_blockwidth, ubwc_blockheight;
   fdl6_get_ubwc_blockwidth(&image->layout,
                            &ubwc_blockwidth, &ubwc_blockheight);
   if (!ubwc_blockwidth) {
      tu_finishme("UBWC for cpp=%d", image->layout.cpp);
      ubwc_enabled = false;
   }

   /* expect UBWC enabled if we asked for it */
   assert(modifier != DRM_FORMAT_MOD_QCOM_COMPRESSED || ubwc_enabled);

   image->layout.ubwc = ubwc_enabled;

   fdl6_layout(&image->layout, vk_format_to_pipe_format(image->vk_format),
               image->samples,
               pCreateInfo->extent.width,
               pCreateInfo->extent.height,
               pCreateInfo->extent.depth,
               pCreateInfo->mipLevels,
               pCreateInfo->arrayLayers,
               pCreateInfo->imageType == VK_IMAGE_TYPE_3D);

   *pImage = tu_image_to_handle(image);

   return VK_SUCCESS;
}

enum a6xx_tex_fetchsize
tu6_fetchsize(VkFormat format)
{
   if (vk_format_description(format)->layout == UTIL_FORMAT_LAYOUT_ASTC)
      return TFETCH6_16_BYTE;

   switch (vk_format_get_blocksize(format) / vk_format_get_blockwidth(format)) {
   case 1: return TFETCH6_1_BYTE;
   case 2: return TFETCH6_2_BYTE;
   case 4: return TFETCH6_4_BYTE;
   case 8: return TFETCH6_8_BYTE;
   case 16: return TFETCH6_16_BYTE;
   default:
      unreachable("bad block size");
   }
}

static uint32_t
tu6_texswiz(const VkComponentMapping *comps,
            VkFormat format,
            VkImageAspectFlagBits aspect_mask)
{
   unsigned char swiz[4] = {comps->r, comps->g, comps->b, comps->a};
   unsigned char vk_swizzle[] = {
      [VK_COMPONENT_SWIZZLE_ZERO] = A6XX_TEX_ZERO,
      [VK_COMPONENT_SWIZZLE_ONE]  = A6XX_TEX_ONE,
      [VK_COMPONENT_SWIZZLE_R] = A6XX_TEX_X,
      [VK_COMPONENT_SWIZZLE_G] = A6XX_TEX_Y,
      [VK_COMPONENT_SWIZZLE_B] = A6XX_TEX_Z,
      [VK_COMPONENT_SWIZZLE_A] = A6XX_TEX_W,
   };
   const unsigned char *fmt_swiz = vk_format_description(format)->swizzle;

   for (unsigned i = 0; i < 4; i++) {
      swiz[i] = (swiz[i] == VK_COMPONENT_SWIZZLE_IDENTITY) ? i : vk_swizzle[swiz[i]];
      /* if format has 0/1 in channel, use that (needed for bc1_rgb) */
      if (swiz[i] < 4) {
         if (aspect_mask == VK_IMAGE_ASPECT_STENCIL_BIT &&
             format == VK_FORMAT_D24_UNORM_S8_UINT)
            swiz[i] = A6XX_TEX_Y;
         switch (fmt_swiz[swiz[i]]) {
         case PIPE_SWIZZLE_0: swiz[i] = A6XX_TEX_ZERO; break;
         case PIPE_SWIZZLE_1: swiz[i] = A6XX_TEX_ONE;  break;
         }
      }
   }

   return A6XX_TEX_CONST_0_SWIZ_X(swiz[0]) |
          A6XX_TEX_CONST_0_SWIZ_Y(swiz[1]) |
          A6XX_TEX_CONST_0_SWIZ_Z(swiz[2]) |
          A6XX_TEX_CONST_0_SWIZ_W(swiz[3]);
}

static enum a6xx_tex_type
tu6_tex_type(VkImageViewType type)
{
   switch (type) {
   default:
   case VK_IMAGE_VIEW_TYPE_1D:
   case VK_IMAGE_VIEW_TYPE_1D_ARRAY:
      return A6XX_TEX_1D;
   case VK_IMAGE_VIEW_TYPE_2D:
   case VK_IMAGE_VIEW_TYPE_2D_ARRAY:
      return A6XX_TEX_2D;
   case VK_IMAGE_VIEW_TYPE_3D:
      return A6XX_TEX_3D;
   case VK_IMAGE_VIEW_TYPE_CUBE:
   case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY:
      return A6XX_TEX_CUBE;
   }
}

void
tu_cs_image_ref(struct tu_cs *cs, const struct tu_image_view *iview, uint32_t layer)
{
   tu_cs_emit(cs, iview->PITCH);
   tu_cs_emit(cs, iview->layer_size >> 6);
   tu_cs_emit_qw(cs, iview->base_addr + iview->layer_size * layer);
}

void
tu_cs_image_ref_2d(struct tu_cs *cs, const struct tu_image_view *iview, uint32_t layer, bool src)
{
   tu_cs_emit_qw(cs, iview->base_addr + iview->layer_size * layer);
   /* SP_PS_2D_SRC_PITCH has shifted pitch field */
   tu_cs_emit(cs, iview->PITCH << (src ? 9 : 0));
}

void
tu_cs_image_flag_ref(struct tu_cs *cs, const struct tu_image_view *iview, uint32_t layer)
{
   tu_cs_emit_qw(cs, iview->ubwc_addr + iview->ubwc_layer_size * layer);
   tu_cs_emit(cs, iview->FLAG_BUFFER_PITCH);
}

void
tu_image_view_init(struct tu_image_view *iview,
                   const VkImageViewCreateInfo *pCreateInfo)
{
   TU_FROM_HANDLE(tu_image, image, pCreateInfo->image);
   const VkImageSubresourceRange *range = &pCreateInfo->subresourceRange;
   VkFormat format = pCreateInfo->format;
   VkImageAspectFlagBits aspect_mask = pCreateInfo->subresourceRange.aspectMask;

   switch (image->type) {
   case VK_IMAGE_TYPE_1D:
   case VK_IMAGE_TYPE_2D:
      assert(range->baseArrayLayer + tu_get_layerCount(image, range) <=
             image->layer_count);
      break;
   case VK_IMAGE_TYPE_3D:
      assert(range->baseArrayLayer + tu_get_layerCount(image, range) <=
             tu_minify(image->extent.depth, range->baseMipLevel));
      break;
   default:
      unreachable("bad VkImageType");
   }

   iview->image = image;

   memset(iview->descriptor, 0, sizeof(iview->descriptor));

   struct fdl_layout *layout = &image->layout;

   uint32_t width = u_minify(image->extent.width, range->baseMipLevel);
   uint32_t height = u_minify(image->extent.height, range->baseMipLevel);
   uint32_t depth = tu_get_layerCount(image, range);
   switch (pCreateInfo->viewType) {
   case VK_IMAGE_VIEW_TYPE_3D:
      depth = u_minify(image->extent.depth, range->baseMipLevel);
      break;
   case VK_IMAGE_VIEW_TYPE_CUBE:
   case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY:
      depth /= 6;
      break;
   default:
      break;
  }

   uint64_t base_addr = image->bo->iova + image->bo_offset +
      fdl_surface_offset(layout, range->baseMipLevel, range->baseArrayLayer);
   uint64_t ubwc_addr = image->bo->iova + image->bo_offset +
      fdl_ubwc_offset(layout, range->baseMipLevel, range->baseArrayLayer);

   uint32_t pitch = layout->slices[range->baseMipLevel].pitch;
   uint32_t ubwc_pitch = layout->ubwc_slices[range->baseMipLevel].pitch;
   uint32_t layer_size = fdl_layer_stride(layout, range->baseMipLevel);

   struct tu_native_format fmt = tu6_format_texture(format, layout->tile_mode);
   /* note: freedreno layout assumes no TILE_ALL bit for non-UBWC
    * this means smaller mipmap levels have a linear tile mode
    */
   fmt.tile_mode = fdl_tile_mode(layout, range->baseMipLevel);

   bool ubwc_enabled = fdl_ubwc_enabled(layout, range->baseMipLevel);

   unsigned fmt_tex = fmt.fmt;
   if (fmt_tex == FMT6_Z24_UNORM_S8_UINT_AS_R8G8B8A8) {
      if (aspect_mask & VK_IMAGE_ASPECT_DEPTH_BIT)
         fmt_tex = FMT6_Z24_UNORM_S8_UINT;
      if (aspect_mask == VK_IMAGE_ASPECT_STENCIL_BIT)
         fmt_tex = FMT6_S8Z24_UINT;
      /* TODO: also use this format with storage descriptor ? */
   }

   iview->descriptor[0] =
      A6XX_TEX_CONST_0_TILE_MODE(fmt.tile_mode) |
      COND(vk_format_is_srgb(format), A6XX_TEX_CONST_0_SRGB) |
      A6XX_TEX_CONST_0_FMT(fmt_tex) |
      A6XX_TEX_CONST_0_SAMPLES(tu_msaa_samples(image->samples)) |
      A6XX_TEX_CONST_0_SWAP(fmt.swap) |
      tu6_texswiz(&pCreateInfo->components, format, aspect_mask) |
      A6XX_TEX_CONST_0_MIPLVLS(tu_get_levelCount(image, range) - 1);
   iview->descriptor[1] = A6XX_TEX_CONST_1_WIDTH(width) | A6XX_TEX_CONST_1_HEIGHT(height);
   iview->descriptor[2] =
      A6XX_TEX_CONST_2_FETCHSIZE(tu6_fetchsize(format)) |
      A6XX_TEX_CONST_2_PITCH(pitch) |
      A6XX_TEX_CONST_2_TYPE(tu6_tex_type(pCreateInfo->viewType));
   iview->descriptor[3] = A6XX_TEX_CONST_3_ARRAY_PITCH(layer_size);
   iview->descriptor[4] = base_addr;
   iview->descriptor[5] = (base_addr >> 32) | A6XX_TEX_CONST_5_DEPTH(depth);

   if (ubwc_enabled) {
      uint32_t block_width, block_height;
      fdl6_get_ubwc_blockwidth(&image->layout,
                               &block_width, &block_height);

      iview->descriptor[3] |= A6XX_TEX_CONST_3_FLAG | A6XX_TEX_CONST_3_TILE_ALL;
      iview->descriptor[7] = ubwc_addr;
      iview->descriptor[8] = ubwc_addr >> 32;
      iview->descriptor[9] |= A6XX_TEX_CONST_9_FLAG_BUFFER_ARRAY_PITCH(layout->ubwc_layer_size >> 2);
      iview->descriptor[10] |=
         A6XX_TEX_CONST_10_FLAG_BUFFER_PITCH(ubwc_pitch) |
         A6XX_TEX_CONST_10_FLAG_BUFFER_LOGW(util_logbase2_ceil(DIV_ROUND_UP(width, block_width))) |
         A6XX_TEX_CONST_10_FLAG_BUFFER_LOGH(util_logbase2_ceil(DIV_ROUND_UP(height, block_height)));
   }

   if (pCreateInfo->viewType == VK_IMAGE_VIEW_TYPE_3D) {
      iview->descriptor[3] |=
         A6XX_TEX_CONST_3_MIN_LAYERSZ(image->layout.slices[image->level_count - 1].size0);
   }

   /* only texture descriptor is valid for TEXTURE-only formats */
   if (!(fmt.supported & FMT_COLOR))
      return;

   struct tu_native_format cfmt = tu6_format_color(format, layout->tile_mode);
   cfmt.tile_mode = fmt.tile_mode;

   if (image->usage & VK_IMAGE_USAGE_STORAGE_BIT) {
      memset(iview->storage_descriptor, 0, sizeof(iview->storage_descriptor));

      iview->storage_descriptor[0] =
         A6XX_IBO_0_FMT(fmt.fmt) |
         A6XX_IBO_0_TILE_MODE(fmt.tile_mode);
      iview->storage_descriptor[1] =
         A6XX_IBO_1_WIDTH(width) |
         A6XX_IBO_1_HEIGHT(height);
      iview->storage_descriptor[2] =
         A6XX_IBO_2_PITCH(pitch) |
         A6XX_IBO_2_TYPE(tu6_tex_type(pCreateInfo->viewType));
      iview->storage_descriptor[3] = A6XX_IBO_3_ARRAY_PITCH(layer_size);

      iview->storage_descriptor[4] = base_addr;
      iview->storage_descriptor[5] = (base_addr >> 32) | A6XX_IBO_5_DEPTH(depth);

      if (ubwc_enabled) {
         iview->storage_descriptor[3] |= A6XX_IBO_3_FLAG | A6XX_IBO_3_UNK27;
         iview->storage_descriptor[7] |= ubwc_addr;
         iview->storage_descriptor[8] |= ubwc_addr >> 32;
         iview->storage_descriptor[9] = A6XX_IBO_9_FLAG_BUFFER_ARRAY_PITCH(layout->ubwc_layer_size >> 2);
         iview->storage_descriptor[10] =
            A6XX_IBO_10_FLAG_BUFFER_PITCH(ubwc_pitch);
      }
   }

   iview->base_addr = base_addr;
   iview->ubwc_addr = ubwc_addr;
   iview->layer_size = layer_size;
   iview->ubwc_layer_size = layout->ubwc_layer_size;

   iview->extent.width = width;
   iview->extent.height = height;
   iview->need_y2_align =
      (fmt.tile_mode == TILE6_LINEAR && range->baseMipLevel != image->level_count - 1);

   iview->ubwc_enabled = ubwc_enabled;

   /* note: these have same encoding for MRT and 2D (except 2D PITCH src) */
   iview->PITCH = A6XX_RB_DEPTH_BUFFER_PITCH(pitch).value;
   iview->FLAG_BUFFER_PITCH = A6XX_RB_DEPTH_FLAG_BUFFER_PITCH(
      .pitch = ubwc_pitch, .array_pitch = layout->ubwc_layer_size >> 2).value;

   iview->RB_MRT_BUF_INFO = A6XX_RB_MRT_BUF_INFO(0,
                              .color_tile_mode = cfmt.tile_mode,
                              .color_format = cfmt.fmt,
                              .color_swap = cfmt.swap).value;
   iview->SP_FS_MRT_REG = A6XX_SP_FS_MRT_REG(0,
                              .color_format = cfmt.fmt,
                              .color_sint = vk_format_is_sint(format),
                              .color_uint = vk_format_is_uint(format)).value;

   iview->SP_PS_2D_SRC_INFO = A6XX_SP_PS_2D_SRC_INFO(
      .color_format = fmt.fmt,
      .tile_mode = fmt.tile_mode,
      .color_swap = fmt.swap,
      .flags = ubwc_enabled,
      .srgb = vk_format_is_srgb(format),
      .samples = tu_msaa_samples(image->samples),
      .samples_average = image->samples > 1 &&
                           !vk_format_is_int(format) &&
                           !vk_format_is_depth_or_stencil(format),
      .unk20 = 1,
      .unk22 = 1).value;
   iview->SP_PS_2D_SRC_SIZE =
      A6XX_SP_PS_2D_SRC_SIZE(.width = width, .height = height).value;

   iview->RB_2D_DST_INFO = A6XX_RB_2D_DST_INFO(
      .color_format = cfmt.fmt,
      .tile_mode = cfmt.tile_mode,
      .color_swap = cfmt.swap,
      .flags = ubwc_enabled,
      .srgb = vk_format_is_srgb(format)).value;

   iview->RB_BLIT_DST_INFO = A6XX_RB_BLIT_DST_INFO(
      .tile_mode = cfmt.tile_mode,
      .samples = tu_msaa_samples(iview->image->samples),
      .color_format = cfmt.fmt,
      .color_swap = cfmt.swap,
      .flags = ubwc_enabled).value;
}

unsigned
tu_image_queue_family_mask(const struct tu_image *image,
                           uint32_t family,
                           uint32_t queue_family)
{
   if (!image->exclusive)
      return image->queue_family_mask;
   if (family == VK_QUEUE_FAMILY_EXTERNAL)
      return (1u << TU_MAX_QUEUE_FAMILIES) - 1u;
   if (family == VK_QUEUE_FAMILY_IGNORED)
      return 1u << queue_family;
   return 1u << family;
}

VkResult
tu_CreateImage(VkDevice device,
               const VkImageCreateInfo *pCreateInfo,
               const VkAllocationCallbacks *pAllocator,
               VkImage *pImage)
{
#ifdef ANDROID
   const VkNativeBufferANDROID *gralloc_info =
      vk_find_struct_const(pCreateInfo->pNext, NATIVE_BUFFER_ANDROID);

   if (gralloc_info)
      return tu_image_from_gralloc(device, pCreateInfo, gralloc_info,
                                   pAllocator, pImage);
#endif

   uint64_t modifier = DRM_FORMAT_MOD_INVALID;
   if (pCreateInfo->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
      const VkImageDrmFormatModifierListCreateInfoEXT *mod_info =
         vk_find_struct_const(pCreateInfo->pNext,
                              IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);

      modifier = DRM_FORMAT_MOD_LINEAR;
      for (unsigned i = 0; i < mod_info->drmFormatModifierCount; i++) {
         if (mod_info->pDrmFormatModifiers[i] == DRM_FORMAT_MOD_QCOM_COMPRESSED)
            modifier = DRM_FORMAT_MOD_QCOM_COMPRESSED;
      }
   } else {
      const struct wsi_image_create_info *wsi_info =
         vk_find_struct_const(pCreateInfo->pNext, WSI_IMAGE_CREATE_INFO_MESA);
      if (wsi_info && wsi_info->scanout)
         modifier = DRM_FORMAT_MOD_LINEAR;
   }

   return tu_image_create(device, pCreateInfo, pAllocator, pImage, modifier);
}

void
tu_DestroyImage(VkDevice _device,
                VkImage _image,
                const VkAllocationCallbacks *pAllocator)
{
   TU_FROM_HANDLE(tu_device, device, _device);
   TU_FROM_HANDLE(tu_image, image, _image);

   if (!image)
      return;

   if (image->owned_memory != VK_NULL_HANDLE)
      tu_FreeMemory(_device, image->owned_memory, pAllocator);

   vk_free2(&device->alloc, pAllocator, image);
}

void
tu_GetImageSubresourceLayout(VkDevice _device,
                             VkImage _image,
                             const VkImageSubresource *pSubresource,
                             VkSubresourceLayout *pLayout)
{
   TU_FROM_HANDLE(tu_image, image, _image);

   const struct fdl_slice *slice = image->layout.slices + pSubresource->mipLevel;

   pLayout->offset = fdl_surface_offset(&image->layout,
                                        pSubresource->mipLevel,
                                        pSubresource->arrayLayer);
   pLayout->size = slice->size0;
   pLayout->rowPitch =
      slice->pitch * vk_format_get_blockheight(image->vk_format);
   pLayout->arrayPitch = image->layout.layer_size;
   pLayout->depthPitch = slice->size0;

   if (image->layout.ubwc_layer_size) {
      /* UBWC starts at offset 0 */
      pLayout->offset = 0;
      /* UBWC scanout won't match what the kernel wants if we have levels/layers */
      assert(image->level_count == 1 && image->layer_count == 1);
   }
}

VkResult tu_GetImageDrmFormatModifierPropertiesEXT(
    VkDevice                                    device,
    VkImage                                     _image,
    VkImageDrmFormatModifierPropertiesEXT*      pProperties)
{
   TU_FROM_HANDLE(tu_image, image, _image);

   assert(pProperties->sType ==
          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT);

   /* TODO invent a modifier for tiled but not UBWC buffers */

   if (!image->layout.tile_mode)
      pProperties->drmFormatModifier = DRM_FORMAT_MOD_LINEAR;
   else if (image->layout.ubwc_layer_size)
      pProperties->drmFormatModifier = DRM_FORMAT_MOD_QCOM_COMPRESSED;
   else
      pProperties->drmFormatModifier = DRM_FORMAT_MOD_INVALID;

   return VK_SUCCESS;
}


VkResult
tu_CreateImageView(VkDevice _device,
                   const VkImageViewCreateInfo *pCreateInfo,
                   const VkAllocationCallbacks *pAllocator,
                   VkImageView *pView)
{
   TU_FROM_HANDLE(tu_device, device, _device);
   struct tu_image_view *view;

   view = vk_alloc2(&device->alloc, pAllocator, sizeof(*view), 8,
                    VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
   if (view == NULL)
      return vk_error(device->instance, VK_ERROR_OUT_OF_HOST_MEMORY);

   tu_image_view_init(view, pCreateInfo);

   *pView = tu_image_view_to_handle(view);

   return VK_SUCCESS;
}

void
tu_DestroyImageView(VkDevice _device,
                    VkImageView _iview,
                    const VkAllocationCallbacks *pAllocator)
{
   TU_FROM_HANDLE(tu_device, device, _device);
   TU_FROM_HANDLE(tu_image_view, iview, _iview);

   if (!iview)
      return;
   vk_free2(&device->alloc, pAllocator, iview);
}

void
tu_buffer_view_init(struct tu_buffer_view *view,
                    struct tu_device *device,
                    const VkBufferViewCreateInfo *pCreateInfo)
{
   TU_FROM_HANDLE(tu_buffer, buffer, pCreateInfo->buffer);

   view->buffer = buffer;

   enum VkFormat vfmt = pCreateInfo->format;
   enum pipe_format pfmt = vk_format_to_pipe_format(vfmt);
   const struct tu_native_format fmt = tu6_format_texture(vfmt, TILE6_LINEAR);

   uint32_t range;
   if (pCreateInfo->range == VK_WHOLE_SIZE)
      range = buffer->size - pCreateInfo->offset;
   else
      range = pCreateInfo->range;
   uint32_t elements = range / util_format_get_blocksize(pfmt);

   static const VkComponentMapping components = {
      .r = VK_COMPONENT_SWIZZLE_R,
      .g = VK_COMPONENT_SWIZZLE_G,
      .b = VK_COMPONENT_SWIZZLE_B,
      .a = VK_COMPONENT_SWIZZLE_A,
   };

   uint64_t iova = tu_buffer_iova(buffer) + pCreateInfo->offset;

   memset(&view->descriptor, 0, sizeof(view->descriptor));

   view->descriptor[0] =
      A6XX_TEX_CONST_0_TILE_MODE(TILE6_LINEAR) |
      A6XX_TEX_CONST_0_SWAP(fmt.swap) |
      A6XX_TEX_CONST_0_FMT(fmt.fmt) |
      A6XX_TEX_CONST_0_MIPLVLS(0) |
      tu6_texswiz(&components, vfmt, VK_IMAGE_ASPECT_COLOR_BIT);
      COND(vk_format_is_srgb(vfmt), A6XX_TEX_CONST_0_SRGB);
   view->descriptor[1] =
      A6XX_TEX_CONST_1_WIDTH(elements & MASK(15)) |
      A6XX_TEX_CONST_1_HEIGHT(elements >> 15);
   view->descriptor[2] =
      A6XX_TEX_CONST_2_UNK4 |
      A6XX_TEX_CONST_2_UNK31;
   view->descriptor[4] = iova;
   view->descriptor[5] = iova >> 32;
}

VkResult
tu_CreateBufferView(VkDevice _device,
                    const VkBufferViewCreateInfo *pCreateInfo,
                    const VkAllocationCallbacks *pAllocator,
                    VkBufferView *pView)
{
   TU_FROM_HANDLE(tu_device, device, _device);
   struct tu_buffer_view *view;

   view = vk_alloc2(&device->alloc, pAllocator, sizeof(*view), 8,
                    VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
   if (!view)
      return vk_error(device->instance, VK_ERROR_OUT_OF_HOST_MEMORY);

   tu_buffer_view_init(view, device, pCreateInfo);

   *pView = tu_buffer_view_to_handle(view);

   return VK_SUCCESS;
}

void
tu_DestroyBufferView(VkDevice _device,
                     VkBufferView bufferView,
                     const VkAllocationCallbacks *pAllocator)
{
   TU_FROM_HANDLE(tu_device, device, _device);
   TU_FROM_HANDLE(tu_buffer_view, view, bufferView);

   if (!view)
      return;

   vk_free2(&device->alloc, pAllocator, view);
}
