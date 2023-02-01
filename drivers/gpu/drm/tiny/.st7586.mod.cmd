cmd_drivers/gpu/drm/tiny/st7586.mod := printf '%s\n'   st7586.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/st7586.mod
