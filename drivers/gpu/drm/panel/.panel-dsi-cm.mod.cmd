cmd_drivers/gpu/drm/panel/panel-dsi-cm.mod := printf '%s\n'   panel-dsi-cm.o | awk '!x[$$0]++ { print("drivers/gpu/drm/panel/"$$0) }' > drivers/gpu/drm/panel/panel-dsi-cm.mod
