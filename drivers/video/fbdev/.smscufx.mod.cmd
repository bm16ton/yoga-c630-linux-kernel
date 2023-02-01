cmd_drivers/video/fbdev/smscufx.mod := printf '%s\n'   smscufx.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/smscufx.mod
