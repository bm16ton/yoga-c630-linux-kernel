// SPDX-License-Identifier: MIT
/*
 * Copyright 2020 Noralf Trønnes
 */

#include <linux/backlight.h>

#include <drm/drm_atomic.h>
#include <drm/drm_atomic_state_helper.h>
#include <drm/drm_connector.h>
#include <drm/drm_drv.h>
#include <drm/drm_encoder.h>
#include <drm/drm_file.h>
#include <drm/drm_modeset_helper_vtables.h>
#include <drm/drm_print.h>
#include <drm/drm_probe_helper.h>
#include <drm/drm_simple_kms_helper.h>
#include <drm/gud_drm.h>

#include "gud_drm_internal.h"

struct gud_drm_connector {
	struct drm_connector connector;
	struct drm_encoder encoder;
	struct backlight_device *backlight;

	u32 flags;

	/* Supported properties */
	u16 *properties;
	unsigned int num_properties;

	/* Initial gadget tv state if applicable, applied on state reset */
	struct drm_tv_connector_state initial_tv_state;

	/*
	 * Initial gadget backlight brightness if applicable, applied on state reset.
	 * The value -ENODEV is used internally to signal no backlight.
	 */
	int initial_brightness;

	/* Supported display modes in transfer format */
	struct gud_drm_display_mode *modes;
	unsigned int num_modes;

	/* EDID */
	void *edid;
	size_t edid_len;
};

static inline struct gud_drm_connector *to_gud_drm_connector(struct drm_connector *connector)
{
	return container_of(connector, struct gud_drm_connector, connector);
}

static int gud_drm_connector_backlight_update_status(struct backlight_device *bd)
{
	struct drm_connector *connector = bl_get_data(bd);
	struct drm_connector_state *connector_state;
	struct drm_device *dev = connector->dev;
	struct drm_modeset_acquire_ctx ctx;
	struct drm_atomic_state *state;
	int ret;

	state = drm_atomic_state_alloc(dev);
	if (!state)
		return -ENOMEM;

	drm_modeset_acquire_init(&ctx, 0);
	state->acquire_ctx = &ctx;
retry:
	connector_state = drm_atomic_get_connector_state(state, connector);
	if (IS_ERR(connector_state)) {
		ret = PTR_ERR(connector_state);
		goto out;
	}

	/* Reuse tv.brightness to avoid having to subclass */
	connector_state->tv.brightness = bd->props.brightness;

	ret = drm_atomic_commit(state);
out:
	if (ret == -EDEADLK) {
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		goto retry;
	}

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	return ret;
}

static int gud_drm_connector_backlight_get_brightness(struct backlight_device *bd)
{
	struct drm_connector *connector = bl_get_data(bd);
	struct drm_device *dev = connector->dev;
	int brightness;

	drm_modeset_lock(&dev->mode_config.connection_mutex, NULL);
	brightness = connector->state->tv.brightness;
	drm_modeset_unlock(&dev->mode_config.connection_mutex);

	return brightness;
}

static const struct backlight_ops gud_drm_connector_backlight_ops = {
	.get_brightness = gud_drm_connector_backlight_get_brightness,
	.update_status	= gud_drm_connector_backlight_update_status,
};

static int gud_drm_connector_backlight_register(struct gud_drm_connector *gconn)
{
	struct drm_connector *connector = &gconn->connector;
	struct backlight_device *bd;
	const char *name;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.scale = BACKLIGHT_SCALE_NON_LINEAR,
		.max_brightness = 100,
	};

	name = kasprintf(GFP_KERNEL, "card%d-%s-backlight",
			 connector->dev->primary->index, connector->name);
	if (!name)
		return -ENOMEM;

	bd = backlight_device_register(name, connector->kdev, connector,
				       &gud_drm_connector_backlight_ops, &props);
	kfree(name);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	gconn->backlight = bd;

	return 0;
}

static void gud_drm_connector_modes_clear(struct gud_drm_connector *gconn)
{
	kfree(gconn->modes);
	gconn->modes = NULL;
	gconn->num_modes = 0;
}

static int gud_drm_connector_modes_get(struct gud_drm_connector *gconn, unsigned int num_modes)
{
	struct gud_drm_device *gdrm = to_gud_drm_device(gconn->connector.dev);
	unsigned int index = gconn->connector.index;
	int ret = 0;

	if (!num_modes)
		goto clear;

	gud_drm_connector_modes_clear(gconn);

	gconn->modes = kmalloc_array(num_modes, sizeof(*gconn->modes), GFP_KERNEL);
	if (!gconn->modes)
		return -ENOMEM;

	gconn->num_modes = num_modes;

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_CONNECTOR_MODES, index,
			      gconn->modes, num_modes * sizeof(*gconn->modes));
	if (ret)
		goto clear;

	return 0;
clear:
	gud_drm_connector_modes_clear(gconn);

	return ret;
}

static void gud_drm_connector_edid_clear(struct gud_drm_connector *gconn)
{
	kfree(gconn->edid);
	gconn->edid = NULL;
	gconn->edid_len = 0;
}

static int gud_drm_connector_edid_get(struct gud_drm_connector *gconn, size_t len)
{
	struct gud_drm_device *gdrm = to_gud_drm_device(gconn->connector.dev);
	unsigned int index = gconn->connector.index;
	int ret = 0;

	if (!len)
		goto clear;

	gud_drm_connector_edid_clear(gconn);

	gconn->edid = kmalloc(len, GFP_KERNEL);
	if (!gconn->edid)
		return -ENOMEM;

	gconn->edid_len = len;

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_CONNECTOR_EDID, index, gconn->edid, len);
	if (ret)
		goto clear;

	return 0;
clear:
	gud_drm_connector_edid_clear(gconn);

	return ret;
}

static int gud_drm_connector_detect_safe(struct drm_connector *connector, bool force)
{
	struct gud_drm_connector *gconn = to_gud_drm_connector(connector);
	struct gud_drm_device *gdrm = to_gud_drm_device(connector->dev);
	struct gud_drm_req_get_connector_status req;
	u16 num_modes, edid_len;
	int status, ret;
	bool changed;

	if (force) {
		ret = gud_drm_usb_set(gdrm, GUD_DRM_USB_REQ_SET_CONNECTOR_FORCE_DETECT,
				      connector->index, NULL, 0);
		if (ret)
			goto free;
	}

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_CONNECTOR_STATUS,
			      connector->index, &req, sizeof(req));
	if (ret)
		goto free;

	changed = req.status & GUD_DRM_CONNECTOR_STATUS_CHANGED;
	status = req.status & GUD_DRM_CONNECTOR_STATUS_MASK;
	if (status > connector_status_unknown)
		status = connector_status_unknown;
	num_modes = le16_to_cpu(req.num_modes);
	edid_len = le16_to_cpu(req.edid_len);

	if (!num_modes && !edid_len) {
		ret = connector_status_disconnected;
		goto free;
	}

	if (!changed && connector->status == status &&
	    gconn->num_modes == num_modes && gconn->edid_len == edid_len)
		return status;

	ret = gud_drm_connector_modes_get(gconn, num_modes);
	if (ret)
		goto free;

	ret = gud_drm_connector_edid_get(gconn, edid_len);
	if (ret)
		goto free;

	return status;
free:
	gud_drm_connector_modes_clear(gconn);
	gud_drm_connector_edid_clear(gconn);

	return ret < 0 ? connector_status_unknown : ret;
}

static int gud_drm_connector_detect(struct drm_connector *connector,
				    struct drm_modeset_acquire_ctx *ctx, bool force)
{
	int idx, ret;

	if (!drm_dev_enter(connector->dev, &idx))
		return -ENODEV;

	ret = gud_drm_connector_detect_safe(connector, force);

	drm_dev_exit(idx);

	return ret;
}

static int gud_drm_connector_get_modes(struct drm_connector *connector)
{
	struct gud_drm_connector *gconn = to_gud_drm_connector(connector);
	unsigned int i, num_modes = 0;

	if (!gconn->num_modes) {
		num_modes = drm_add_edid_modes(connector, gconn->edid);
		goto out;
	}

	for (i = 0; i < gconn->num_modes; i++) {
		struct drm_display_mode *mode;

		mode = drm_mode_create(connector->dev);
		if (!mode)
			goto out;

		gud_drm_to_display_mode(mode, &gconn->modes[i]);

		drm_mode_probed_add(connector, mode);
		num_modes++;
	}
out:
	if (gconn->edid_len)
		drm_connector_update_edid_property(connector, gconn->edid);

	return num_modes;
}

static int gud_drm_connector_atomic_check(struct drm_connector *connector,
					  struct drm_atomic_state *state)
{
	struct drm_connector_state *new_state;
	struct drm_crtc_state *new_crtc_state;
	struct drm_connector_state *old_state;

	new_state = drm_atomic_get_new_connector_state(state, connector);
	if (!new_state->crtc)
		return 0;

	old_state = drm_atomic_get_old_connector_state(state, connector);
	new_crtc_state = drm_atomic_get_new_crtc_state(state, new_state->crtc);

	if (old_state->tv.subconnector != new_state->tv.subconnector ||
	    old_state->tv.margins.left != new_state->tv.margins.left ||
	    old_state->tv.margins.right != new_state->tv.margins.right ||
	    old_state->tv.margins.top != new_state->tv.margins.top ||
	    old_state->tv.margins.bottom != new_state->tv.margins.bottom ||
	    old_state->tv.mode != new_state->tv.mode ||
	    old_state->tv.brightness != new_state->tv.brightness ||
	    old_state->tv.contrast != new_state->tv.contrast ||
	    old_state->tv.flicker_reduction != new_state->tv.flicker_reduction ||
	    old_state->tv.overscan != new_state->tv.overscan ||
	    old_state->tv.saturation != new_state->tv.saturation ||
	    old_state->tv.hue != new_state->tv.hue)
		new_crtc_state->connectors_changed = true;

	return 0;
}

static const struct drm_connector_helper_funcs gud_drm_connector_helper_funcs = {
	.detect_ctx = gud_drm_connector_detect,
	.get_modes = gud_drm_connector_get_modes,
	.atomic_check = gud_drm_connector_atomic_check,
};

static int gud_drm_connector_late_register(struct drm_connector *connector)
{
	struct gud_drm_connector *gconn = to_gud_drm_connector(connector);

	if (gconn->initial_brightness < 0)
		return 0;

	return gud_drm_connector_backlight_register(gconn);
}

static void gud_drm_connector_early_unregister(struct drm_connector *connector)
{
	struct gud_drm_connector *gconn = to_gud_drm_connector(connector);

	backlight_device_unregister(gconn->backlight);
}

static void gud_drm_connector_destroy(struct drm_connector *connector)
{
	struct gud_drm_connector *gconn = to_gud_drm_connector(connector);

	drm_connector_cleanup(connector);
	gud_drm_connector_modes_clear(gconn);
	gud_drm_connector_edid_clear(gconn);
	kfree(gconn->properties);
	kfree(gconn);
}

static void gud_drm_connector_reset(struct drm_connector *connector)
{
	struct gud_drm_connector *gconn = to_gud_drm_connector(connector);

	drm_atomic_helper_connector_reset(connector);
	connector->state->tv = gconn->initial_tv_state;
	/* Set margins from command line */
	drm_atomic_helper_connector_tv_reset(connector);
	if (gconn->initial_brightness >= 0)
		connector->state->tv.brightness = gconn->initial_brightness;
}

static const struct drm_connector_funcs gud_drm_connector_funcs = {
	.fill_modes = drm_helper_probe_single_connector_modes,
	.late_register = gud_drm_connector_late_register,
	.early_unregister = gud_drm_connector_early_unregister,
	.destroy = gud_drm_connector_destroy,
	.reset = gud_drm_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
};

/*
 * The tv.mode property is shared among the connectors and its enum names are
 * driver specific. This means that if more than one connector uses tv.mode,
 * the enum names has to be the same.
 */
static int gud_drm_connector_add_tv_mode(struct gud_drm_device *gdrm,
					 struct drm_connector *connector, u64 val)
{
	unsigned int i, num_modes;
	const char **modes;
	size_t buf_len;
	char *buf;
	int ret;

	num_modes = val >> GUD_DRM_USB_CONNECTOR_TV_MODE_NUM_SHIFT;

	if (!num_modes)
		return -EINVAL;

	buf_len = num_modes * DRM_PROP_NAME_LEN;
	modes = kmalloc_array(num_modes, sizeof(*modes), GFP_KERNEL);
	buf = kmalloc(buf_len, GFP_KERNEL);
	if (!modes || !buf) {
		ret = -ENOMEM;
		goto free;
	}

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_CONNECTOR_TV_MODE_VALUES,
			      connector->index, buf, buf_len);
	if (ret)
		goto free;

	for (i = 0; i < num_modes; i++)
		modes[i] = &buf[i * DRM_PROP_NAME_LEN];

	ret = drm_mode_create_tv_properties(connector->dev, num_modes, modes);
free:
	kfree(modes);
	kfree(buf);

	return ret;
}

static struct drm_property *
gud_drm_connector_property_lookup(struct drm_connector *connector, u16 prop)
{
	struct drm_mode_config *config = &connector->dev->mode_config;

	switch (prop) {
	case GUD_DRM_PROPERTY_TV_SELECT_SUBCONNECTOR:
		return config->tv_select_subconnector_property;
	case GUD_DRM_PROPERTY_TV_LEFT_MARGIN:
		return config->tv_left_margin_property;
	case GUD_DRM_PROPERTY_TV_RIGHT_MARGIN:
		return config->tv_right_margin_property;
	case GUD_DRM_PROPERTY_TV_TOP_MARGIN:
		return config->tv_top_margin_property;
	case GUD_DRM_PROPERTY_TV_BOTTOM_MARGIN:
		return config->tv_bottom_margin_property;
	case GUD_DRM_PROPERTY_TV_MODE:
		return config->tv_mode_property;
	case GUD_DRM_PROPERTY_TV_BRIGHTNESS:
		return config->tv_brightness_property;
	case GUD_DRM_PROPERTY_TV_CONTRAST:
		return config->tv_contrast_property;
	case GUD_DRM_PROPERTY_TV_FLICKER_REDUCTION:
		return config->tv_flicker_reduction_property;
	case GUD_DRM_PROPERTY_TV_OVERSCAN:
		return config->tv_overscan_property;
	case GUD_DRM_PROPERTY_TV_SATURATION:
		return config->tv_saturation_property;
	case GUD_DRM_PROPERTY_TV_HUE:
		return config->tv_hue_property;
	default:
		return ERR_PTR(-EINVAL);
	}
}

static unsigned int *gud_drm_connector_tv_state_val(u16 prop, struct drm_tv_connector_state *state)
{
	switch (prop) {
	case GUD_DRM_PROPERTY_TV_SELECT_SUBCONNECTOR:
		return &state->subconnector;
	case GUD_DRM_PROPERTY_TV_LEFT_MARGIN:
		return &state->margins.left;
	case GUD_DRM_PROPERTY_TV_RIGHT_MARGIN:
		return &state->margins.right;
	case GUD_DRM_PROPERTY_TV_TOP_MARGIN:
		return &state->margins.top;
	case GUD_DRM_PROPERTY_TV_BOTTOM_MARGIN:
		return &state->margins.bottom;
	case GUD_DRM_PROPERTY_TV_MODE:
		return &state->mode;
	case GUD_DRM_PROPERTY_TV_BRIGHTNESS:
		return &state->brightness;
	case GUD_DRM_PROPERTY_TV_CONTRAST:
		return &state->contrast;
	case GUD_DRM_PROPERTY_TV_FLICKER_REDUCTION:
		return &state->flicker_reduction;
	case GUD_DRM_PROPERTY_TV_OVERSCAN:
		return &state->overscan;
	case GUD_DRM_PROPERTY_TV_SATURATION:
		return &state->saturation;
	case GUD_DRM_PROPERTY_TV_HUE:
		return &state->hue;
	default:
		return ERR_PTR(-EINVAL);
	}
}

static int gud_drm_connector_add_properties(struct gud_drm_device *gdrm,
					    struct gud_drm_connector *gconn,
					    unsigned int num_properties)
{
	struct drm_device *drm = &gdrm->drm;
	struct drm_connector *connector = &gconn->connector;
	struct gud_drm_property *properties;
	bool need_tv_props = false;
	unsigned int i;
	int ret;

	gconn->properties = kcalloc(num_properties, sizeof(*gconn->properties), GFP_KERNEL);
	if (!gconn->properties)
		return -ENOMEM;

	properties = kcalloc(num_properties, sizeof(*properties), GFP_KERNEL);
	if (!properties)
		return -ENOMEM;

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_CONNECTOR_PROPERTIES, connector->index,
			      properties, num_properties * sizeof(*properties));
	if (ret)
		goto out;

	for (i = 0; i < num_properties; i++) {
		u16 prop = le16_to_cpu(properties[i].prop);
		u64 val = le64_to_cpu(properties[i].val);

		drm_dbg(drm, "property: %u = %llu(0x%llx)\n", prop, val, val);

		switch (prop) {
		case GUD_DRM_PROPERTY_TV_LEFT_MARGIN:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_RIGHT_MARGIN:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_TOP_MARGIN:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_BOTTOM_MARGIN:
			ret = drm_mode_create_tv_margin_properties(drm);
			if (ret)
				goto out;
			break;
		case GUD_DRM_PROPERTY_TV_MODE:
			ret = gud_drm_connector_add_tv_mode(gdrm, connector, val);
			if (ret)
				goto out;
			break;
		case GUD_DRM_PROPERTY_TV_SELECT_SUBCONNECTOR:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_BRIGHTNESS:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_CONTRAST:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_FLICKER_REDUCTION:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_OVERSCAN:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_SATURATION:
			fallthrough;
		case GUD_DRM_PROPERTY_TV_HUE:
			need_tv_props = true;
			break;
		case GUD_DRM_PROPERTY_BACKLIGHT_BRIGHTNESS:
			if (val > 100) {
				ret = -EINVAL;
				goto out;
			}
			gconn->initial_brightness = val;
			break;
		default:
			/* New ones might show up in future devices, skip those we don't know. */
			drm_dbg(drm, "Unknown property: %u\n", prop);
			continue;
		}

		gconn->properties[gconn->num_properties++] = prop;
	}

	if (!gconn->num_properties)
		goto out;

	if (need_tv_props) {
		/* This is a no-op if already added. */
		ret = drm_mode_create_tv_properties(drm, 0, NULL);
		if (ret)
			goto out;
	}

	for (i = 0; i < num_properties; i++) {
		u16 prop = le16_to_cpu(properties[i].prop);
		u64 val = le64_to_cpu(properties[i].val);
		struct drm_property *property;
		unsigned int *state_val;

		switch (prop) {
		case GUD_DRM_PROPERTY_BACKLIGHT_BRIGHTNESS:
			/* not a DRM property */
			continue;
		case GUD_DRM_PROPERTY_TV_MODE:
			val = val & (BIT(GUD_DRM_USB_CONNECTOR_TV_MODE_NUM_SHIFT) - 1);
			break;
		}

		property = gud_drm_connector_property_lookup(connector, prop);
		if (IS_ERR(property))
			continue;

		state_val = gud_drm_connector_tv_state_val(prop, &gconn->initial_tv_state);
		if (IS_ERR(state_val))
			continue;

		*state_val = val;
		drm_object_attach_property(&connector->base, property, 0);
	}
out:
	kfree(properties);

	return ret;
}

int gud_drm_connector_fill_properties(struct drm_connector *connector,
				      struct drm_connector_state *connector_state,
				      struct gud_drm_property *properties)
{
	struct gud_drm_connector *gconn;
	unsigned int i;

	gconn = to_gud_drm_connector(connector);

	/* Only interested in the count? */
	if (!connector_state)
		return gconn->num_properties;

	for (i = 0; i < gconn->num_properties; i++) {
		u16 prop = gconn->properties[i];
		u64 val;

		if (prop == GUD_DRM_PROPERTY_BACKLIGHT_BRIGHTNESS) {
			val = connector_state->tv.brightness;
		} else {
			unsigned int *state_val;

			state_val = gud_drm_connector_tv_state_val(prop, &connector_state->tv);
			if (WARN_ON_ONCE(IS_ERR(state_val)))
				return PTR_ERR(state_val);

			val = *state_val;
		}

		properties[i].prop = cpu_to_le16(prop);
		properties[i].val = cpu_to_le64(val);
	}

	return gconn->num_properties;
}

int gud_drm_connector_create(struct gud_drm_device *gdrm, unsigned int index)
{
	struct gud_drm_req_get_connector desc;
	struct drm_device *drm = &gdrm->drm;
	struct gud_drm_connector *gconn;
	struct drm_connector *connector;
	struct drm_encoder *encoder;
	int ret;

	ret = gud_drm_usb_get(gdrm, GUD_DRM_USB_REQ_GET_CONNECTOR, index, &desc, sizeof(desc));
	if (ret)
		return ret;

	drm_dbg(drm, "index=%u type=%u flags=0x%x num_properties=%u\n", index,
		desc.connector_type, le32_to_cpu(desc.flags), desc.num_properties);

	/* REVISIT: This needs to be updated as new types are added */
	if (desc.connector_type > DRM_MODE_CONNECTOR_SPI)
		return -EINVAL;

	gconn = kzalloc(sizeof(*gconn), GFP_KERNEL);
	if (!gconn)
		return -ENOMEM;

	gconn->initial_brightness = -ENODEV;
	gconn->flags = le32_to_cpu(desc.flags);
	connector = &gconn->connector;

	drm_connector_helper_add(connector, &gud_drm_connector_helper_funcs);
	ret = drm_connector_init(drm, connector, &gud_drm_connector_funcs, desc.connector_type);
	if (ret) {
		kfree(connector);
		return ret;
	}

	if (WARN_ON(connector->index != index))
		return -EINVAL;

	if (gconn->flags & GUD_DRM_CONNECTOR_FLAGS_POLL)
		connector->polled = (DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT);

	if (desc.num_properties) {
		ret = gud_drm_connector_add_properties(gdrm, gconn, desc.num_properties);
		if (ret) {
			dev_err(drm->dev, "Failed to add connector/%u properties\n", index);
			return ret;
		}
	}

	/* The first connector is attached to the existing simple pipe encoder */
	if (!connector->index) {
		encoder = &gdrm->pipe.encoder;
	} else {
		encoder = &gconn->encoder;

		ret = drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_NONE);
		if (ret)
			return ret;

		encoder->possible_crtcs = 1;
	}

	return drm_connector_attach_encoder(connector, encoder);
}
