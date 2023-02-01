cmd_drivers/video/backlight/bd6107.mod := printf '%s\n'   bd6107.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/bd6107.mod
