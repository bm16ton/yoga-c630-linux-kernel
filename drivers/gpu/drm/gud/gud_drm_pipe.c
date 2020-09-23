// SPDX-License-Identifier: MIT
/*
 * Copyright 2020 Noralf Trønnes
 */

#include <linux/dma-buf.h>
#include <linux/lz4.h>
#include <linux/usb.h>
#include <linux/workqueue.h>

#include <drm/drm_atomic.h>
#include <drm/drm_connector.h>
#include <drm/drm_damage_helper.h>
#include <drm/drm_drv.h>
#include <drm/drm_format_helper.h>
#include <drm/drm_fourcc.h>
#include <drm/drm_framebuffer.h>
#include <drm/drm_gem_shmem_helper.h>
#include <drm/drm_print.h>
#include <drm/drm_rect.h>
#include <drm/drm_simple_kms_helper.h>
#include <drm/gud_drm.h>

#include "gud_drm_internal.h"

static bool gud_drm_is_big_endian(void)
{
#if defined(__BIG_ENDIAN)
	return true;
#else
	return false;
#endif
}

static size_t gud_drm_xrgb8888_to_r124(u8 *dst, const struct drm_format_info *format,
				       void *src, struct drm_framebuffer *fb,
				       struct drm_rect *rect)
{
	unsigned int block_width = drm_format_info_block_width(format, 0);
	unsigned int bits_per_pixel = 8 / block_width;
	unsigned int x, y, width, height;
	u8 *p, *block = dst; /* Assign to silence compiler warning */
	size_t len;
	void *buf;

	WARN_ON_ONCE(format->char_per_block[0] != 1);

	/* Start on a byte boundary */
	rect->x1 = ALIGN_DOWN(rect->x1, block_width);
	width = drm_rect_width(rect);
	height = drm_rect_height(rect);
	len = drm_format_info_min_pitch(format, 0, width) * height;

	buf = kmalloc(width * height, GFP_KERNEL);
	if (!buf)
		return len; /* To keep logic simple, just transmit garbage */

	drm_fb_xrgb8888_to_gray8(buf, src, fb, rect);

	p = buf;
	for (y = 0; y < drm_rect_height(rect); y++) {
		for (x = 0; x < drm_rect_width(rect); x++) {
			if (!(x % block_width)) {
				block = dst++;
				*block = 0;
			}

			*block <<= bits_per_pixel;
			*block |= (*p++) >> (8 - bits_per_pixel);
		}
	}

	kfree(buf);

	return len;
}

static int gud_drm_fb_flush(struct gud_drm_device *gdrm, struct drm_framebuffer *fb,
			    const struct drm_format_info *format, struct drm_rect *rect)
{
	struct dma_buf_attachment *import_attach = fb->obj[0]->import_attach;
	struct gud_drm_req_set_buffer req;
	size_t pitch, len, trlen;
	int actual_length;
	void *vaddr, *buf;
	int ret = 0;

	drm_dbg(&gdrm->drm, "Flushing [FB:%d] " DRM_RECT_FMT " imported=%s\n",
		fb->base.id, DRM_RECT_ARG(rect), import_attach ? "yes" : "no");

	pitch = drm_format_info_min_pitch(format, 0, drm_rect_width(rect));
	len = pitch * drm_rect_height(rect);
	if (len > gdrm->bulk_len)
		return -E2BIG;

	vaddr = drm_gem_shmem_vmap(fb->obj[0]);
	if (!vaddr)
		return -ENOMEM;

	if (import_attach) {
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf, DMA_FROM_DEVICE);
		if (ret)
			goto vunmap;
	}

	if (gdrm->compression & GUD_DRM_COMPRESSION_LZ4)
		buf = gdrm->compress_buf;
	else
		buf = gdrm->bulk_buf;

	/*
	 * Imported buffers are assumed to be write-combined and thus uncached
	 * with slow reads (at least on ARM).
	 */
	if (format != fb->format) {
		if (format->format == GUD_DRM_FORMAT_R1)
			len = gud_drm_xrgb8888_to_r124(buf, format, vaddr, fb, rect);
		else if (format->format == DRM_FORMAT_RGB565)
			drm_fb_xrgb8888_to_rgb565(buf, vaddr, fb, rect, gud_drm_is_big_endian());
	} else if (gud_drm_is_big_endian() && format->cpp[0] > 1) {
		drm_fb_swab(buf, vaddr, fb, rect, !import_attach);
	} else if (gdrm->compression && !import_attach && pitch == fb->pitches[0]) {
		/* can compress directly from the framebuffer */
		buf = vaddr + rect->y1 * pitch;
	} else {
		drm_fb_memcpy(buf, vaddr, fb, rect);
	}

	req.x = cpu_to_le32(rect->x1);
	req.y = cpu_to_le32(rect->y1);
	req.width = cpu_to_le32(drm_rect_width(rect));
	req.height = cpu_to_le32(drm_rect_height(rect));
	req.length = cpu_to_le32(len);
	req.compression = 0;
	req.compressed_length = 0;

	if (gdrm->compression & GUD_DRM_COMPRESSION_LZ4) {
		ret = LZ4_compress_default(buf, gdrm->bulk_buf, len, len, gdrm->lz4_comp_mem);
		if (ret > 0)
			req.compression = GUD_DRM_COMPRESSION_LZ4;
	}

	trlen = len;

	if (ret > 0) {
		req.compressed_length = cpu_to_le32(ret);
		trlen = ret;
	} else if (buf == gdrm->compress_buf) {
		/*
		 * Compression failed (buffer didn't compress well).
		 * compress_buf is vmalloc'ed so we need to copy.
		 */
		memcpy(gdrm->bulk_buf, gdrm->compress_buf, len);
	}

	if (import_attach)
		dma_buf_end_cpu_access(import_attach->dmabuf, DMA_FROM_DEVICE);

	gdrm->stats_length += len;
	/* Did it wrap around? */
	if (gdrm->stats_length <= len && gdrm->stats_actual_length) {
		gdrm->stats_length = len;
		gdrm->stats_actual_length = 0;
	}
	gdrm->stats_actual_length += trlen;

	/*
	 * This will wait if decompress/copy from the previous flush is still in
	 * process on the gadget side.
	 */
	ret = gud_drm_usb_set(gdrm, GUD_DRM_USB_REQ_SET_BUFFER, 0, &req, sizeof(req));
	if (ret)
		goto vunmap;

	ret = usb_bulk_msg(gdrm->usb, gdrm->bulk_pipe, gdrm->bulk_buf, trlen,
			   &actual_length, msecs_to_jiffies(3000));
	if (!ret && trlen != actual_length)
		ret = -EIO;
	if (ret)
		gdrm->stats_num_errors++;
vunmap:
	drm_gem_shmem_vunmap(fb->obj[0], vaddr);

	return ret;
}

void gud_drm_clear_damage(struct gud_drm_device *gdrm)
{
	gdrm->damage.x1 = INT_MAX;
	gdrm->damage.y1 = INT_MAX;
	gdrm->damage.x2 = 0;
	gdrm->damage.y2 = 0;
}

void gud_drm_work(struct work_struct *work)
{
	struct gud_drm_device *gdrm = container_of(work, struct gud_drm_device, work);
	const struct drm_format_info *format;
	struct drm_framebuffer *fb;
	struct drm_rect damage;
	unsigned int i, lines;
	int idx, ret = 0;
	size_t pitch;

	if (!drm_dev_enter(&gdrm->drm, &idx))
		return;

	mutex_lock(&gdrm->damage_lock);
	fb = gdrm->fb;
	gdrm->fb = NULL;
	damage = gdrm->damage;
	gud_drm_clear_damage(gdrm);
	mutex_unlock(&gdrm->damage_lock);

	if (!fb)
		goto out;

	format = fb->format;
	if (format->format == DRM_FORMAT_XRGB8888 && gdrm->xrgb8888_emulation_format)
		format = gdrm->xrgb8888_emulation_format;

	/* Split update if it's too big */
	pitch = drm_format_info_min_pitch(format, 0, drm_rect_width(&damage));
	lines = drm_rect_height(&damage);

	if (gdrm->bulk_len < lines * pitch)
		lines = gdrm->bulk_len / pitch;

	for (i = 0; i < DIV_ROUND_UP(drm_rect_height(&damage), lines); i++) {
		struct drm_rect rect = damage;

		rect.y1 += i * lines;
		rect.y2 = min_t(u32, rect.y1 + lines, damage.y2);

		ret = gud_drm_fb_flush(gdrm, fb, format, &rect);
		if (ret &&
		    (ret != -ENODEV && ret != -ECONNRESET && ret != -ESHUTDOWN && ret != -EPROTO))
			dev_err_once(fb->dev->dev, "Failed to flush framebuffer: error=%d\n", ret);
	}

	drm_framebuffer_put(fb);
out:
	drm_dev_exit(idx);
}

static void gud_drm_fb_queue_damage(struct gud_drm_device *gdrm,
				    struct drm_framebuffer *fb,
				    struct drm_rect *damage)
{
	struct drm_framebuffer *old_fb = NULL;

	mutex_lock(&gdrm->damage_lock);

	if (fb != gdrm->fb) {
		old_fb = gdrm->fb;
		drm_framebuffer_get(fb);
		gdrm->fb = fb;
	}

	gdrm->damage.x1 = min(gdrm->damage.x1, damage->x1);
	gdrm->damage.y1 = min(gdrm->damage.y1, damage->y1);
	gdrm->damage.x2 = max(gdrm->damage.x2, damage->x2);
	gdrm->damage.y2 = max(gdrm->damage.y2, damage->y2);

	mutex_unlock(&gdrm->damage_lock);

	queue_work(system_long_wq, &gdrm->work);

	if (old_fb)
		drm_framebuffer_put(old_fb);
}

int gud_drm_pipe_check(struct drm_simple_display_pipe *pipe,
		       struct drm_plane_state *new_plane_state,
		       struct drm_crtc_state *new_crtc_state)
{
	struct gud_drm_device *gdrm = to_gud_drm_device(pipe->crtc.dev);
	struct drm_plane_state *old_plane_state = pipe->plane.state;
	const struct drm_display_mode *mode = &new_crtc_state->mode;
	struct drm_atomic_state *state = new_plane_state->state;
	struct drm_framebuffer *old_fb = old_plane_state->fb;
	struct drm_connector_state *connector_state = NULL;
	struct drm_framebuffer *fb = new_plane_state->fb;
	const struct drm_format_info *format = fb->format;
	struct gud_drm_req_set_state *req;
	struct drm_connector *connector;
	int idx, ret, num_properties;
	unsigned int i;
	size_t len;

	if (WARN_ON_ONCE(!fb))
		return -EINVAL;

	if (old_plane_state->rotation != new_plane_state->rotation)
		new_crtc_state->mode_changed = true;

	if (old_fb && old_fb->format != format)
		new_crtc_state->mode_changed = true;

	if (!new_crtc_state->mode_changed && !new_crtc_state->connectors_changed)
		return 0;

	/* Only one connector is supported */
	if (hweight32(new_crtc_state->connector_mask) != 1)
		return -EINVAL;

	if (format->format == DRM_FORMAT_XRGB8888 && gdrm->xrgb8888_emulation_format)
		format = gdrm->xrgb8888_emulation_format;

	for_each_new_connector_in_state(state, connector, connector_state, i)
		break;

	if (!connector_state) {
		struct drm_connector_list_iter conn_iter;

		/* We always send the full state to the device, so get the connector state */

		drm_connector_list_iter_begin(pipe->crtc.dev, &conn_iter);
		drm_for_each_connector_iter(connector, &conn_iter) {
			if (new_crtc_state->connector_mask & drm_connector_mask(connector))
				break;
		}
		drm_connector_list_iter_end(&conn_iter);

		if (WARN_ON_ONCE(!connector))
			return -ENOENT;

		connector_state = drm_atomic_get_connector_state(state, connector);
		if (IS_ERR(connector_state))
			return PTR_ERR(connector_state);
	}

	num_properties = gud_drm_connector_fill_properties(connector, NULL, NULL);
	if (num_properties < 0)
		return num_properties;

	num_properties += gdrm->num_properties;

	len = struct_size(req, properties, num_properties);
	req = kzalloc(len, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	gud_drm_from_display_mode(&req->mode, mode);

	req->format = cpu_to_le32(format->format);
	req->connector = drm_connector_index(connector);
	req->num_properties = num_properties;

	num_properties = gud_drm_connector_fill_properties(connector, connector_state,
							   req->properties);

	for (i = 0; i < gdrm->num_properties; i++) {
		u16 prop = gdrm->properties[i];
		u64 val;

		switch (prop) {
		case GUD_DRM_PROPERTY_ROTATION:
			val = new_plane_state->rotation;
			break;
		default:
			WARN_ON_ONCE(1);
			ret = -EINVAL;
			goto out;
		}

		req->properties[num_properties + i].prop = cpu_to_le16(prop);
		req->properties[num_properties + i].val = cpu_to_le64(val);
	}

	if (!drm_dev_enter(fb->dev, &idx)) {
		ret = -ENODEV;
		goto out;
	}

	ret = gud_drm_usb_set(gdrm, GUD_DRM_USB_REQ_SET_STATE_CHECK, 0, req, len);

	drm_dev_exit(idx);
out:
	kfree(req);

	return ret;
}

void gud_drm_pipe_update(struct drm_simple_display_pipe *pipe,
			 struct drm_plane_state *old_state)
{
	struct drm_device *drm = pipe->crtc.dev;
	struct gud_drm_device *gdrm = to_gud_drm_device(drm);
	struct drm_plane_state *state = pipe->plane.state;
	struct drm_framebuffer *fb = state->fb;
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_rect damage;
	int idx;

	if (!drm_dev_enter(drm, &idx))
		return;

	if (!old_state->fb)
		gud_drm_usb_write8(gdrm, GUD_DRM_USB_REQ_SET_CONTROLLER_ENABLE, 1);

	if (fb && (crtc->state->mode_changed || crtc->state->connectors_changed))
		gud_drm_usb_set(gdrm, GUD_DRM_USB_REQ_SET_STATE_COMMIT, 0, NULL, 0);

	if (crtc->state->active_changed)
		gud_drm_usb_write8(gdrm, GUD_DRM_USB_REQ_SET_DISPLAY_ENABLE, crtc->state->active);

	if (drm_atomic_helper_damage_merged(old_state, state, &damage))
		gud_drm_fb_queue_damage(gdrm, fb, &damage);

	if (!fb) {
		cancel_work_sync(&gdrm->work);

		mutex_lock(&gdrm->damage_lock);
		if (gdrm->fb) {
			drm_framebuffer_put(gdrm->fb);
			gdrm->fb = NULL;
		}
		gud_drm_clear_damage(gdrm);
		mutex_unlock(&gdrm->damage_lock);

		gud_drm_usb_write8(gdrm, GUD_DRM_USB_REQ_SET_CONTROLLER_ENABLE, 0);
	}

	drm_dev_exit(idx);
}
