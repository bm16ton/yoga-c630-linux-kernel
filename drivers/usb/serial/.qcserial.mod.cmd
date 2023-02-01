cmd_drivers/usb/serial/qcserial.mod := printf '%s\n'   qcserial.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/qcserial.mod
