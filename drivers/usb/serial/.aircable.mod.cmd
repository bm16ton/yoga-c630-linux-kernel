cmd_drivers/usb/serial/aircable.mod := printf '%s\n'   aircable.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/aircable.mod
