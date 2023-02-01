cmd_drivers/video/vgastate.mod := printf '%s\n'   vgastate.o | awk '!x[$$0]++ { print("drivers/video/"$$0) }' > drivers/video/vgastate.mod
