cmd_drivers/media/usb/go7007/go7007-loader.mod := printf '%s\n'   go7007-loader.o | awk '!x[$$0]++ { print("drivers/media/usb/go7007/"$$0) }' > drivers/media/usb/go7007/go7007-loader.mod
