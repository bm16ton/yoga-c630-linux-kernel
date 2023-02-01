cmd_drivers/gpu/drm/gud/gud.mod := printf '%s\n'   gud_drv.o gud_pipe.o gud_connector.o | awk '!x[$$0]++ { print("drivers/gpu/drm/gud/"$$0) }' > drivers/gpu/drm/gud/gud.mod
