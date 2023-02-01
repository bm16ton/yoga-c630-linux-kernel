cmd_drivers/gpu/drm/bridge/display-connector.mod := printf '%s\n'   display-connector.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/display-connector.mod
