cmd_drivers/gpu/drm/bridge/ti-dlpc3433.mod := printf '%s\n'   ti-dlpc3433.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/ti-dlpc3433.mod
