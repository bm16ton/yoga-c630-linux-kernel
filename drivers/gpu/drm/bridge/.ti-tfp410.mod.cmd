cmd_drivers/gpu/drm/bridge/ti-tfp410.mod := printf '%s\n'   ti-tfp410.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/"$$0) }' > drivers/gpu/drm/bridge/ti-tfp410.mod
