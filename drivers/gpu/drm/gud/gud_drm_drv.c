// SPDX-License-Identifier: MIT
/*
 * Copyright 2020 Noralf Trønnes
 */

#include <linux/dma-buf.h>
#include <linux/lz4.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/string_helpers.h>
#include <linux/usb.h>
#include <linux/workqueue.h>

#include <drm/drm_atomic_helper.h>
#include <drm/drm_damage_helper.h>
#include <drm/drm_debugfs.h>
#include <drm/drm_drv.h>
#include <drm/drm_fb_helper.h>
#include <drm/drm_fourcc.h>
#include <drm/drm_gem_shmem_helper.h>
#include <drm/drm_gem_framebuffer_helper.h>
#include <drm/drm_managed.h>
#include <drm/drm_print.h>
#include <drm/drm_probe_helper.h>
#include <drm/drm_simple_kms_helper.h>
#include <drm/gud_drm.h>

#include "gud_drm_internal.h"

/* Only used internally */
static const struct drm_format_info gud_drm_format_r1 = {
	.format = GUD_DRM_FORMAT_R1,
	.num_planes = 1,
	.char_per_block = { 1, 0, 0 },
	.block_w = { 8, 0, 0 },
	.block_h = { 1, 0, 0 },
	.hsub = 1,
	.vsub = 1,
};

static int gud_drm_usb_control_msg(struct usb_device *usb, u8 ifnum, bool in,
				   u8 request, u16 value, void *buf, size_t len,
				   bool check_len)
{
	u8 requesttype = USB_TYPE_VENDOR | USB_RECIP_INTERFACE;
	unsigned int pipe;
	int ret;

	if (in) {
		pipe = usb_rcvctrlpipe(usb, 0);
		requesttype |= USB_DIR_IN;
	} else {
		pipe = usb_sndctrlpipe(usb, 0);
		requesttype |= USB_DIR_OUT;
	}

	ret = usb_control_msg(usb, pipe, request, requesttype, value,
			      ifnum, buf, len, USB_CTRL_GET_TIMEOUT);

	if (check_len && ret >= 0) {
		if (ret != len)
			ret = -EIO;
		else
			ret = 0;
	}

	return ret;
}

static int gud_get_vendor_descriptor(struct usb_interface *interface,
				     struct gud_drm_display_descriptor *desc)
{
	u8 ifnum = interface->cur_altsetting->desc.bInterfaceNumber;
	struct usb_device *usb = interface_to_usbdev(interface);
	void *buf;
	int ret;

	buf = kmalloc(sizeof(*desc), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = gud_drm_usb_control_msg(usb, ifnum, true, USB_REQ_GET_DESCRIPTOR,
				      GUD_DRM_USB_DT_DISPLAY << 8, buf, sizeof(*desc), false);

	memcpy(desc, buf, sizeof(*desc));
	kfree(buf);

	if (ret < 0)
		return ret;

	if (ret != sizeof(*desc) || desc->bLength != sizeof(*desc) ||
	    desc->bDescriptorType != GUD_DRM_USB_DT_DISPLAY)
		return -ENODATA;

	DRM_DEV_DEBUG_DRIVER(&interface->dev,
			     "Version=%u Compression=0x%x NumFormats=%u NumConnectors=%u MaxBufferSizeOrder=%u\n",
			     desc->bVersion, desc->bCompression, desc->bNumFormats,
			     desc->bNumConnectors, desc->bMaxBufferSizeOrder);

	if (!desc->bVersion || !desc->bNumFormats || !desc->bNumConnectors ||
	    !desc->bMaxBufferSizeOrder || !desc->dwMaxWidth || !desc->dwMaxHeight ||
	    le32_to_cpu(desc->dwMinWidth) > le32_to_cpu(desc->dwMaxWidth) ||
	    le32_to_cpu(desc->dwMinHeight) > le32_to_cpu(desc->dwMaxHeight))
		return -EINVAL;

	return 0;
}

static int gud_usb_get_status(struct usb_device *usb, u8 ifnum)
{
	struct gud_drm_req_get_status *status;
	int ret, status_retries = 2000 / 5; /* maximum wait ~2 seconds */
	unsigned long delay = 500;

	status = kmalloc(sizeof(*status), GFP_KERNEL);
	if (!status)
		return -ENOMEM;

	/*
	 * Poll due to lack of data/status stage control on the gadget side.
	 *
	 * If we did not use polling and gave up here after waiting 2 seconds,
	 * the worker in the gadget would finally get to queuing up the status
	 * respons, but by that time the host has moved on. The gadget side
	 * (at least dwc2) would now be left in a non-recoverable state.
	 *
	 * Worst case commit timeout in DRM can be tens of seconds (wait for
	 * various _done completions).
	 */
	while (status_retries--) {
		ret = gud_drm_usb_control_msg(usb, ifnum, true, USB_REQ_GET_STATUS, 0,
					      status, sizeof(*status), true);
		if (ret)
			goto out;

		if (!(status->flags & GUD_DRM_STATUS_PENDING)) {
			ret = -status->errno;
			goto out;
		}

		usleep_range(delay, delay + 1000);

		if (delay < 4500)
			delay += 1000;
	}

	ret = -ETIMEDOUT;
out:
	kfree(status);

	return ret;
}

static int gud_usb_transfer(struct gud_drm_device *gdrm, bool in, u8 request,
			    u16 index, void *buf, size_t len)
{
	int idx, ret;

	drm_dbg(&gdrm->drm, "%s: request=0x%x index=%u len=%zu\n",
		in ? "get" : "set", request, index, len);

	if (len > GUD_DRM_MAX_TRANSFER_SIZE)
		return -ENOMEM;

	if (!drm_dev_enter(&gdrm->drm, &idx))
		return -ENODEV;

	mutex_lock(&gdrm->ctrl_lock);

	if (!in && buf)
		memcpy(gdrm->ctrl_msg_buf, buf, len);

	ret = gud_drm_usb_control_msg(gdrm->usb, gdrm->ifnum, in, request, index,
				      gdrm->ctrl_msg_buf, len, true);

	/*
	 * OUT transfers are processed in a worker on the gadget side after
	 * reception so we always need to check status. IN transfers are
	 * processed in the interrupt handler and will halt on error letting us
	 * know something went wrong.
	 */
	if (ret || !in) {
		ret = gud_usb_get_status(gdrm->usb, gdrm->ifnum);
		if (ret)
			goto error;
	}

	if (in && buf)
		memcpy(buf, gdrm->ctrl_msg_buf, len);
error:
	if (ret) {
		drm_dbg(&gdrm->drm, "ret=%d\n", ret);
		gdrm->stats_num_errors++;
	}

	mutex_unlock(&gdrm->ctrl_lock);
	drm_dev_exit(idx);

	return ret;
}

int gud_drm_usb_get(struct gud_drm_device *gdrm, u8 request, u16 index, void *buf, size_t len)
{
	return gud_usb_transfer(gdrm, true, request, index, buf, len);
}

int gud_drm_usb_set(struct gud_drm_device *gdrm, u8 request, u16 index, void *buf, size_t len)
{
	return gud_usb_transfer(gdrm, false, request, index, buf, len);
}

int gud_drm_usb_write8(struct gud_drm_device *gdrm, u8 request, u8 val)
{
	return gud_drm_usb_set(gdrm, request, 0, &val, sizeof(val));
}

static int gud_drm_usb_read32(struct gud_drm_device *gdrm, u8 request,
			      u32 *vals, unsigned int num_vals)
{
	unsigned int i;
	int ret;

	ret = gud_drm_usb_get(gdrm, request, 0, vals, num_vals * sizeof(*vals));
	if (ret)
		return ret;

	for (i = 0; i < num_vals; i++)
		vals[i] = le32_to_cpu((__le32)vals[i]);

	return 0;
}

static int gud_drm_get_properties(struct gud_drm_device *gdrm, unsigned int num_properties)
{
	struct gud_drm_property *properties;
	unsigned int i;
	int ret;

	if (!num_properties)
		return 0;

	gdrm->properties = kcalloc(num_properties, sizeof(*gdrm->properties), GFP_KERNEL);
	if (!gdrm->properties)
		return -ENOMEM;

	properties = kcalloc(num_properties, sizeof(*properties), GFP_KERNEL);
	if (!properties)
		return -ENOMEM;

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_PROPERTIES, 0,
			      properties, num_properties * sizeof(*properties));
	if (ret)
		goto out;

	for (i = 0; i < num_properties; i++) {
		u16 prop = le16_to_cpu(properties[i].prop);
		u64 val = le64_to_cpu(properties[i].val);

		switch (prop) {
		case GUD_DRM_PROPERTY_ROTATION:
			ret = drm_plane_create_rotation_property(&gdrm->pipe.plane,
								 DRM_MODE_ROTATE_0, val);
			break;
		default:
			/* New ones might show up in future devices, skip those we don't know. */
			drm_dbg(&gdrm->drm, "Unknown property: %u\n", prop);
			continue;
		}

		if (ret)
			goto out;

		gdrm->properties[gdrm->num_properties++] = prop;
	}
out:
	kfree(properties);

	return ret;
}

static struct drm_gem_object *
gud_drm_driver_gem_create_object(struct drm_device *dev, size_t size)
{
	struct drm_gem_shmem_object *shmem;

	shmem = kzalloc(sizeof(*shmem), GFP_KERNEL);
	if (!shmem)
		return NULL;

	/*
	 * This doesn't make a difference on x86, but on ARM (pi4) it was
	 * necessary to avoid black lines all over and it made it possible to
	 * compress directly from the framebuffer without performance drop.
	 */
	shmem->map_cached = true;

	return &shmem->base;
}

static int gud_drm_stats_debugfs(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct gud_drm_device *gdrm = to_gud_drm_device(node->minor->dev);
	char buf[10];

	string_get_size(gdrm->bulk_len, 1, STRING_UNITS_2, buf, sizeof(buf));
	seq_printf(m, "Max buffer size: %s\n", buf);
	seq_printf(m, "Number of errors:  %u\n", gdrm->stats_num_errors);

	seq_puts(m, "Compression:      ");
	if (gdrm->compression & GUD_DRM_COMPRESSION_LZ4)
		seq_puts(m, " lz4");
	seq_puts(m, "\n");

	if (gdrm->compression) {
		u64 remainder;
		u64 ratio = div64_u64_rem(gdrm->stats_length, gdrm->stats_actual_length,
					  &remainder);
		u64 ratio_frac = div64_u64(remainder * 10, gdrm->stats_actual_length);

		seq_printf(m, "Compression ratio: %llu.%llu\n", ratio, ratio_frac);
	}

	return 0;
}

static const struct drm_info_list gud_drm_debugfs_list[] = {
	{ "stats", gud_drm_stats_debugfs, 0, NULL },
};

static void gud_drm_driver_debugfs_init(struct drm_minor *minor)
{
	drm_debugfs_create_files(gud_drm_debugfs_list, ARRAY_SIZE(gud_drm_debugfs_list),
				 minor->debugfs_root, minor);
}

static const struct drm_simple_display_pipe_funcs gud_drm_pipe_funcs = {
	.check      = gud_drm_pipe_check,
	.update	    = gud_drm_pipe_update,
	.prepare_fb = drm_gem_fb_simple_display_pipe_prepare_fb,
};

static const struct drm_mode_config_funcs gud_drm_mode_config_funcs = {
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
};

static const uint64_t gud_drm_pipe_modifiers[] = {
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
};

DEFINE_DRM_GEM_FOPS(gud_drm_fops);

static struct drm_driver gud_drm_driver = {
	.driver_features	= DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.fops			= &gud_drm_fops,
	.gem_create_object	= gud_drm_driver_gem_create_object,
	DRM_GEM_SHMEM_DRIVER_OPS,
	.debugfs_init		= gud_drm_driver_debugfs_init,

	.name			= "gud_drm",
	.desc			= "Generic USB Display",
	.date			= "20200422",
	.major			= 1,
	.minor			= 0,
};

static void gud_drm_free_buffers_and_mutex(void *data)
{
	struct gud_drm_device *gdrm = data;

	/* Access to these are protected by drm_dev_enter/exit */

	kfree(gdrm->properties);
	vfree(gdrm->compress_buf);
	kfree(gdrm->bulk_buf);
	kfree(gdrm->ctrl_msg_buf);
	gdrm->properties = NULL;
	gdrm->compress_buf = NULL;
	gdrm->bulk_buf = NULL;
	gdrm->ctrl_msg_buf = NULL;

	mutex_destroy(&gdrm->ctrl_lock);
	mutex_destroy(&gdrm->damage_lock);
}

static int gud_drm_probe(struct usb_interface *interface,
			 const struct usb_device_id *id)
{
	u8 ifnum = interface->cur_altsetting->desc.bInterfaceNumber;
	struct usb_device *usb = interface_to_usbdev(interface);
	struct device *dev = &interface->dev;
	const struct drm_format_info *xrgb8888_emulation_format = NULL;
	u32 *formats, *formats_dev, num_connectors, num_formats = 0;
	bool rgb565_supported = false, rgb8888_supported = false;
	struct usb_endpoint_descriptor *bulk_out;
	struct gud_drm_display_descriptor desc;
	struct gud_drm_device *gdrm;
	struct drm_device *drm;
	size_t max_buffer_size;
	int ret, i;

	ret = usb_find_bulk_out_endpoint(interface->cur_altsetting, &bulk_out);
	if (ret)
		return ret;

	ret = gud_get_vendor_descriptor(interface, &desc);
	if (ret) {
		DRM_DEV_DEBUG_DRIVER(dev, "Not a display interface: ret=%d\n", ret);
		return -ENODEV;
	}

	if (desc.bVersion > 1) {
		u8 *version = kmalloc(sizeof(*version), GFP_KERNEL);

		if (!version)
			return -ENOMEM;

		/* Check if the device can support us */
		*version = 1;
		ret = gud_drm_usb_control_msg(usb, ifnum, false, GUD_DRM_USB_REQ_SET_VERSION,
					      0, version, sizeof(*version), true);
		if (!ret)
			ret = gud_usb_get_status(usb, ifnum);
		kfree(version);
		if (ret) {
			dev_err(dev, "Protocol version %u is not supported\n", desc.bVersion);
			return -EPROTONOSUPPORT;
		}

		desc.bVersion = 1;
	}

	num_connectors = desc.bNumConnectors;
	max_buffer_size = 1 << desc.bMaxBufferSizeOrder;

	gdrm = devm_drm_dev_alloc(dev, &gud_drm_driver, struct gud_drm_device, drm);
	if (IS_ERR(gdrm))
		return PTR_ERR(gdrm);

	drm = &gdrm->drm;
	drm->mode_config.funcs = &gud_drm_mode_config_funcs;
	ret = drmm_mode_config_init(drm);
	if (ret)
		return ret;

	gdrm->usb = usb;
	gdrm->ifnum = ifnum;
	gdrm->compression = desc.bCompression & GUD_DRM_COMPRESSION_LZ4;

	mutex_init(&gdrm->ctrl_lock);
	mutex_init(&gdrm->damage_lock);
	INIT_WORK(&gdrm->work, gud_drm_work);
	gud_drm_clear_damage(gdrm);

	/*
	 * devm_kmalloc() places struct devres at the beginning of the buffer it
	 * allocates. This can waste a lot of memory when allocating
	 * power-of-two sized buffers. Asking for 4k would actually allocate 8k.
	 */

	ret = devm_add_action_or_reset(dev, gud_drm_free_buffers_and_mutex, gdrm);
	if (ret)
		return ret;

	gdrm->ctrl_msg_buf = kmalloc(GUD_DRM_MAX_TRANSFER_SIZE, GFP_KERNEL);
	if (!gdrm->ctrl_msg_buf)
		return -ENOMEM;
retry:
	gdrm->bulk_buf = kmalloc(max_buffer_size, GFP_KERNEL);
	if (!gdrm->bulk_buf) {
		max_buffer_size /= 2;
		if (max_buffer_size < SZ_2M) { /* Give up if we can't do 1024x768 RGB565 */
			return -ENOMEM;
		}
		goto retry;
	}

	gdrm->bulk_pipe = usb_sndbulkpipe(gdrm->usb, usb_endpoint_num(bulk_out));
	gdrm->bulk_len = max_buffer_size;

	if (gdrm->compression & GUD_DRM_COMPRESSION_LZ4) {
		gdrm->lz4_comp_mem = devm_kmalloc(dev, LZ4_MEM_COMPRESS, GFP_KERNEL);
		if (!gdrm->lz4_comp_mem)
			return -ENOMEM;

		gdrm->compress_buf = vmalloc(gdrm->bulk_len);
		if (!gdrm->compress_buf)
			return -ENOMEM;
	}

	drm->mode_config.min_width = le32_to_cpu(desc.dwMinWidth);
	drm->mode_config.max_width = le32_to_cpu(desc.dwMaxWidth);
	drm->mode_config.min_height = le32_to_cpu(desc.dwMinHeight);
	drm->mode_config.max_height = le32_to_cpu(desc.dwMaxHeight);

	formats_dev = devm_kmalloc_array(dev, desc.bNumFormats, sizeof(u32), GFP_KERNEL);
	/* Add room for emulated XRGB8888 */
	formats = devm_kmalloc_array(dev, desc.bNumFormats + 1, sizeof(u32), GFP_KERNEL);
	if (!formats_dev || !formats)
		return -ENOMEM;

	ret = gud_drm_usb_read32(gdrm, GUD_DRM_USB_REQ_GET_FORMATS, formats_dev, desc.bNumFormats);
	if (ret)
		return ret;

	for (i = 0; i < desc.bNumFormats; i++) {
		const struct drm_format_info *fmt_info;
		u32 format = formats_dev[i];

		if (format == GUD_DRM_FORMAT_R1) {
			fmt_info = &gud_drm_format_r1;
		} else {
			/* This will trigger a WARN for unknown formats... */
			fmt_info = drm_format_info(format);
			if (!fmt_info) {
				drm_dbg(drm, "Unknown format: 0x%x\n", format);
				continue;
			}
		}

		switch (format) {
		case DRM_FORMAT_XRGB8888:
			fallthrough;
		case DRM_FORMAT_ARGB8888:
			rgb8888_supported = true;
			break;
		case DRM_FORMAT_RGB888:
			fallthrough;
		case DRM_FORMAT_BGR888:
			drm_dbg(drm, "24-bit formats are not supported.\n");
			continue;
		case DRM_FORMAT_RGB565:
			rgb565_supported = true;
			if (!xrgb8888_emulation_format)
				xrgb8888_emulation_format = fmt_info;
			break;
		case GUD_DRM_FORMAT_R1:
			if (!xrgb8888_emulation_format)
				xrgb8888_emulation_format = fmt_info;
			/* Internal, not for userspace */
			continue;
		}

		formats[num_formats++] = format;
	}

	if (!num_formats && !xrgb8888_emulation_format) {
		dev_err(dev, "No supported formats found\n");
		return -ENOENT;
	}

	/* Prefer speed over color depth */
	if (rgb565_supported)
		drm->mode_config.preferred_depth = 16;

	if (!rgb8888_supported && xrgb8888_emulation_format) {
		gdrm->xrgb8888_emulation_format = xrgb8888_emulation_format;
		formats[num_formats++] = DRM_FORMAT_XRGB8888;
	}

	ret = drm_simple_display_pipe_init(drm, &gdrm->pipe, &gud_drm_pipe_funcs,
					   formats, num_formats,
					   gud_drm_pipe_modifiers, NULL);
	if (ret)
		return ret;

	devm_kfree(dev, formats);
	devm_kfree(dev, formats_dev);

	ret = gud_drm_get_properties(gdrm, desc.bNumProperties);
	if (ret)
		return ret;

	drm_plane_enable_fb_damage_clips(&gdrm->pipe.plane);

	for (i = 0; i < num_connectors; i++) {
		ret = gud_drm_connector_create(gdrm, i);
		if (ret)
			return ret;
	}

	drm_mode_config_reset(drm);

	usb_set_intfdata(interface, gdrm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		return ret;

	drm_kms_helper_poll_init(drm);

	drm_fbdev_generic_setup(drm, 0);

	return 0;
}

static void gud_drm_disconnect(struct usb_interface *interface)
{
	struct gud_drm_device *gdrm = usb_get_intfdata(interface);
	struct drm_device *drm = &gdrm->drm;

	drm_dbg(drm, "%s:\n", __func__);

	drm_kms_helper_poll_fini(drm);
	drm_dev_unplug(drm);
	drm_atomic_helper_shutdown(drm);
}

static int gud_drm_suspend(struct usb_interface *interface, pm_message_t message)
{
	struct gud_drm_device *gdrm = usb_get_intfdata(interface);

	return drm_mode_config_helper_suspend(&gdrm->drm);
}

static int gud_drm_resume(struct usb_interface *interface)
{
	struct gud_drm_device *gdrm = usb_get_intfdata(interface);

	drm_mode_config_helper_resume(&gdrm->drm);

	return 0;
}

static const struct usb_device_id gud_drm_table[] = {
	{ USB_DEVICE_INTERFACE_CLASS(0x1d50, 0x614d, USB_CLASS_VENDOR_SPEC) },
	{ }
};

MODULE_DEVICE_TABLE(usb, gud_drm_table);

static struct usb_driver gud_drm_usb_driver = {
	.name		= "gud_drm",
	.probe		= gud_drm_probe,
	.disconnect	= gud_drm_disconnect,
	.id_table	= gud_drm_table,
	.suspend	= gud_drm_suspend,
	.resume		= gud_drm_resume,
	.reset_resume	= gud_drm_resume,
};

module_usb_driver(gud_drm_usb_driver);

MODULE_AUTHOR("Noralf Trønnes");
MODULE_LICENSE("Dual MIT/GPL");
