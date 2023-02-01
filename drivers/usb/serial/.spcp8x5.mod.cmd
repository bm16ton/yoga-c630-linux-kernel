cmd_drivers/usb/serial/spcp8x5.mod := printf '%s\n'   spcp8x5.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/spcp8x5.mod
