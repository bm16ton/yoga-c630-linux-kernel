cmd_drivers/usb/serial/ch341.mod := printf '%s\n'   ch341.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ch341.mod
