cmd_drivers/video/fbdev/tdfxfb.mod := printf '%s\n'   tdfxfb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/tdfxfb.mod
