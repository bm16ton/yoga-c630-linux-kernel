cmd_drivers/gpu/drm/tiny/mi0283qt.mod := printf '%s\n'   mi0283qt.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/mi0283qt.mod
