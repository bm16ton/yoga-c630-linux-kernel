cmd_drivers/gpu/drm/drm_mipi_dbi.mod := printf '%s\n'   drm_mipi_dbi.o | awk '!x[$$0]++ { print("drivers/gpu/drm/"$$0) }' > drivers/gpu/drm/drm_mipi_dbi.mod
