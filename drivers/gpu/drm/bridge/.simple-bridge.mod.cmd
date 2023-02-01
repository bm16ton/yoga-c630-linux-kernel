cmd_drivers/gpu/drm/bridge/simple-bridge.mod := printf '%s\n'   simple-bridge.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/simple-bridge.mod
