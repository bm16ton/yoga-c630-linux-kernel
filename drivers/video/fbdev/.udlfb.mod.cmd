cmd_drivers/video/fbdev/udlfb.mod := printf '%s\n'   udlfb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/udlfb.mod
