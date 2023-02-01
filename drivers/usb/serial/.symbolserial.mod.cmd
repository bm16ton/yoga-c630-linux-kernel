cmd_drivers/usb/serial/symbolserial.mod := printf '%s\n'   symbolserial.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/symbolserial.mod
