cmd_drivers/usb/serial/quatech2.mod := printf '%s\n'   quatech2.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/quatech2.mod
