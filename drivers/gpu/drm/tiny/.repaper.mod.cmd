cmd_drivers/gpu/drm/tiny/repaper.mod := printf '%s\n'   repaper.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/repaper.mod
