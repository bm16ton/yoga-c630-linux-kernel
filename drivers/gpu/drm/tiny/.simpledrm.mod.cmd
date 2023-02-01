cmd_drivers/gpu/drm/tiny/simpledrm.mod := printf '%s\n'   simpledrm.o | awk '!x[$$0]++ { print("drivers/gpu/drm/tiny/"$$0) }' > drivers/gpu/drm/tiny/simpledrm.mod
