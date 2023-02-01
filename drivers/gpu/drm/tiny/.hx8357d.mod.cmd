cmd_drivers/gpu/drm/tiny/hx8357d.mod := printf '%s\n'   hx8357d.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/hx8357d.mod
