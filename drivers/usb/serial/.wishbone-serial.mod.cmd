cmd_drivers/usb/serial/wishbone-serial.mod := printf '%s\n'   wishbone-serial.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/wishbone-serial.mod
