cmd_drivers/gpu/drm/tiny/gm12u320.mod := printf '%s\n'   gm12u320.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/gm12u320.mod
