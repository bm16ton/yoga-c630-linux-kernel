cmd_drivers/video/fbdev/pm3fb.mod := printf '%s\n'   pm3fb.o | awk '!x[$$0]++ { print("drivers/video/fbdev/"$$0) }' > drivers/video/fbdev/pm3fb.mod
