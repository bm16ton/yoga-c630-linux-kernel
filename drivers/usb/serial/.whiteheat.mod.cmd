cmd_drivers/usb/serial/whiteheat.mod := printf '%s\n'   whiteheat.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/whiteheat.mod
