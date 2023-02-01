cmd_drivers/media/usb/go7007/s2250.mod := printf '%s\n'   s2250-board.o | awk '!x[$$0]++ { print("drivers/media/usb/go7007/"$$0) }' > drivers/media/usb/go7007/s2250.mod
