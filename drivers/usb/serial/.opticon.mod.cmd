cmd_drivers/usb/serial/opticon.mod := printf '%s\n'   opticon.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/opticon.mod
