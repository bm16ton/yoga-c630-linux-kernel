cmd_drivers/gpu/drm/drm_ttm_helper.mod := printf '%s\n'   drm_gem_ttm_helper.o | awk '!x[$$0]++ { print("drivers/gpu/drm/"$$0) }' > drivers/gpu/drm/drm_ttm_helper.mod
