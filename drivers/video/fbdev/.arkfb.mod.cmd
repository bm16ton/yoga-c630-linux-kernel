cmd_drivers/video/fbdev/arkfb.mod := printf '%s\n'   arkfb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/arkfb.mod
