cmd_drivers/usb/serial/xr_serial.mod := printf '%s\n'   xr_serial.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/xr_serial.mod
