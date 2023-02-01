cmd_drivers/gpu/drm/hisilicon/kirin/dw_drm_dsi.mod := printf '%s\n'   dw_drm_dsi.o | awk '!x[$$0]++ { print("drivers/gpu/drm/hisilicon/kirin/"$$0) }' > drivers/gpu/drm/hisilicon/kirin/dw_drm_dsi.mod
