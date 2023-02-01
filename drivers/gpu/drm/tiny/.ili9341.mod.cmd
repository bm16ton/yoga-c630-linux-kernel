cmd_drivers/gpu/drm/tiny/ili9341.mod := printf '%s\n'   ili9341.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/ili9341.mod
