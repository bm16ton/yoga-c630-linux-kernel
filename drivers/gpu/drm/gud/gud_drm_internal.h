/* SPDX-License-Identifier: MIT */

#ifndef __LINUX_GUD_DRM_INTERNAL_H
#define __LINUX_GUD_DRM_INTERNAL_H

#include <linux/workqueue.h>
#include <linux/list.h>
#include <linux/mutex.h>

#include <drm/drm_simple_kms_helper.h>

struct gud_drm_device {
	struct drm_device drm;
	struct drm_simple_display_pipe pipe;
	struct work_struct work;
	struct usb_device *usb;
	u8 ifnum;
	const struct drm_format_info *xrgb8888_emulation_format;

	u16 *properties;
	unsigned int num_properties;

	unsigned int bulk_pipe;
	void *bulk_buf;
	size_t bulk_len;

	u8 compression;
	void *lz4_comp_mem;
	void *compress_buf;

	u64 stats_length;
	u64 stats_actual_length;
	unsigned int stats_num_errors;

	struct mutex ctrl_lock; /* Serialize req and status transfers */
	void *ctrl_msg_buf;

	struct mutex damage_lock; /* Protects the following members: */
	struct drm_framebuffer *fb;
	struct drm_rect damage;
};

static inline struct gud_drm_device *to_gud_drm_device(struct drm_device *drm)
{
	return container_of(drm, struct gud_drm_device, drm);
}

int gud_drm_usb_get(struct gud_drm_device *gdrm, u8 request, u16 index, void *buf, size_t len);
int gud_drm_usb_set(struct gud_drm_device *gdrm, u8 request, u16 index, void *buf, size_t len);
int gud_drm_usb_write8(struct gud_drm_device *gdrm, u8 request, u8 val);

void gud_drm_clear_damage(struct gud_drm_device *gdrm);
void gud_drm_work(struct work_struct *work);
int gud_drm_pipe_check(struct drm_simple_display_pipe *pipe,
		       struct drm_plane_state *new_plane_state,
		       struct drm_crtc_state *new_crtc_state);
void gud_drm_pipe_update(struct drm_simple_display_pipe *pipe,
			 struct drm_plane_state *old_state);

int gud_drm_connector_fill_properties(struct drm_connector *connector,
				      struct drm_connector_state *connector_state,
				      struct gud_drm_property *properties);
int gud_drm_connector_create(struct gud_drm_device *gdrm, unsigned int index);

#endif
