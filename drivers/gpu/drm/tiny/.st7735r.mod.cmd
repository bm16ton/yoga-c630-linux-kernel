cmd_drivers/gpu/drm/tiny/st7735r.mod := printf '%s\n'   st7735r.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/st7735r.mod
