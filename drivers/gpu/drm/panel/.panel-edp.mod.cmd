cmd_drivers/gpu/drm/panel/panel-edp.mod := printf '%s\n'   panel-edp.o | awk '!x[$$0]++ { print("drivers/gpu/drm/panel/"$$0) }' > drivers/gpu/drm/panel/panel-edp.mod
