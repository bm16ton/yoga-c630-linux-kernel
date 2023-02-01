cmd_drivers/gpu/drm/drm_dma_helper.mod := printf '%s\n'   drm_gem_dma_helper.o drm_fb_dma_helper.o | awk '!x[$$0]++ { print("drivers/gpu/drm/"$$0) }' > drivers/gpu/drm/drm_dma_helper.mod
