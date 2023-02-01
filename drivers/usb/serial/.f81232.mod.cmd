cmd_drivers/usb/serial/f81232.mod := printf '%s\n'   f81232.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/f81232.mod
