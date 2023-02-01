cmd_drivers/gpu/drm/bridge/ti-sn65dsi86.mod := printf '%s\n'   ti-sn65dsi86.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/ti-sn65dsi86.mod
