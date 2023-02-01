cmd_drivers/gpu/drm/panel/panel-lvds.mod := printf '%s\n'   panel-lvds.o | awk '!x[$$0]++ { print("drivers/gpu/drm/panel/"$$0) }' > drivers/gpu/drm/panel/panel-lvds.mod
