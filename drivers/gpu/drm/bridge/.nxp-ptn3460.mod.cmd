cmd_drivers/gpu/drm/bridge/nxp-ptn3460.mod := printf '%s\n'   nxp-ptn3460.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/nxp-ptn3460.mod
