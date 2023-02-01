cmd_drivers/video/fbdev/simplefb.mod := printf '%s\n'   simplefb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/simplefb.mod
