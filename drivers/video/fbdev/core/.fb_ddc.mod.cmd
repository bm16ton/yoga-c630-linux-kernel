cmd_drivers/video/fbdev/core/fb_ddc.mod := printf '%s\n'   fb_ddc.o | awk '!x[$$0]++ { print("drivers/video/fbdev/core/"$$0) }' > drivers/video/fbdev/core/fb_ddc.mod
