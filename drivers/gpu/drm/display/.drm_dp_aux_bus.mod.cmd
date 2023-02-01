cmd_drivers/gpu/drm/display/drm_dp_aux_bus.mod := printf '%s\n'   drm_dp_aux_bus.o | awk '!x[$$0]++ { print("drivers/gpu/drm/display/"$$0) }' > drivers/gpu/drm/display/drm_dp_aux_bus.mod
