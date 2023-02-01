cmd_drivers/gpu/drm/drm_vram_helper.mod := printf '%s\n'   drm_gem_vram_helper.o | awk '!x[$$0]++ { print("drivers/gpu/drm/"$$0) }' > drivers/gpu/drm/drm_vram_helper.mod
