cmd_drivers/usb/serial/f81534.mod := printf '%s\n'   f81534.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/f81534.mod
