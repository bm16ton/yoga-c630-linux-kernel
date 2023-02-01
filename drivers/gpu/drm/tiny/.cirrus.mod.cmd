cmd_drivers/gpu/drm/tiny/cirrus.mod := printf '%s\n'   cirrus.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/cirrus.mod
