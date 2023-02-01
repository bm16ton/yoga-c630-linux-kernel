cmd_drivers/gpu/drm/bridge/lvds-codec.mod := printf '%s\n'   lvds-codec.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/lvds-codec.mod
