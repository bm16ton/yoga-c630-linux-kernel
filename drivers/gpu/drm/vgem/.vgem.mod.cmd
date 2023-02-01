cmd_drivers/gpu/drm/vgem/vgem.mod := printf '%s\n'   vgem_drv.o vgem_fence.o | awk '!x[$$0]++ { print("drivers/gpu/drm/vgem/"$$0) }' > drivers/gpu/drm/vgem/vgem.mod
