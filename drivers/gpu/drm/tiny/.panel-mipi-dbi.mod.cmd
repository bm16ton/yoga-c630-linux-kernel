cmd_drivers/gpu/drm/tiny/panel-mipi-dbi.mod := printf '%s\n'   panel-mipi-dbi.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/panel-mipi-dbi.mod
