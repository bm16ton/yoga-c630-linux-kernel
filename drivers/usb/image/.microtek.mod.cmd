cmd_drivers/usb/image/microtek.mod := printf '%s\n'   microtek.o | awk '!x[$$0]++ { print("drivers/usb/image/"$$0) }' > drivers/usb/image/microtek.mod
