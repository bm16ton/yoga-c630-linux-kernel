cmd_drivers/usb/serial/visor.mod := printf '%s\n'   visor.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/visor.mod
