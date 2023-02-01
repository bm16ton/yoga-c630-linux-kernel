cmd_drivers/gpu/drm/meson/meson_dw_hdmi.mod := printf '%s\n'   meson_dw_hdmi.o | awk '!x[$$0]++ { print("drivers/gpu/drm/meson/"$$0) }' > drivers/gpu/drm/meson/meson_dw_hdmi.mod
