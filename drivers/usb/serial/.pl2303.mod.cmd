cmd_drivers/usb/serial/pl2303.mod := printf '%s\n'   pl2303.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/pl2303.mod
