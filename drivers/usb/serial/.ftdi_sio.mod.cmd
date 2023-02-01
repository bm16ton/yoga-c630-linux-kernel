cmd_drivers/usb/serial/ftdi_sio.mod := printf '%s\n'   ftdi_sio.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ftdi_sio.mod
