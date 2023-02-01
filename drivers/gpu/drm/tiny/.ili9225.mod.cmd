cmd_drivers/gpu/drm/tiny/ili9225.mod := printf '%s\n'   ili9225.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/ili9225.mod
