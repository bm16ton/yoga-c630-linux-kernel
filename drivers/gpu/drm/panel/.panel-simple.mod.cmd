cmd_drivers/gpu/drm/panel/panel-simple.mod := printf '%s\n'   panel-simple.o | awk '!x[$$0]++ { print("drivers/gpu/drm/panel/"$$0) }' > drivers/gpu/drm/panel/panel-simple.mod
