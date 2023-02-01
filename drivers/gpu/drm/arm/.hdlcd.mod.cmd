cmd_drivers/gpu/drm/arm/hdlcd.mod := printf '%s\n'   hdlcd_drv.o hdlcd_crtc.o | awk '!x[$$0]++ { print("drivers/gpu/drm/arm/"$$0) }' > drivers/gpu/drm/arm/hdlcd.mod
