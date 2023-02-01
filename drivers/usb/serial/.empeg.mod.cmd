cmd_drivers/usb/serial/empeg.mod := printf '%s\n'   empeg.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/empeg.mod
