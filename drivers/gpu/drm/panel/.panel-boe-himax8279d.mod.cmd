cmd_drivers/gpu/drm/panel/panel-boe-himax8279d.mod := printf '%s\n'   panel-boe-himax8279d.o | awk '!x[$$0]++ { print("drivers/gpu/drm/panel/"$$0) }' > drivers/gpu/drm/panel/panel-boe-himax8279d.mod
