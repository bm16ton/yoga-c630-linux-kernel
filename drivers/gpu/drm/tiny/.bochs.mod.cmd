cmd_drivers/gpu/drm/tiny/bochs.mod := printf '%s\n'   bochs.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/bochs.mod
