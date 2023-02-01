cmd_drivers/usb/serial/safe_serial.mod := printf '%s\n'   safe_serial.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/safe_serial.mod
