cmd_drivers/usb/serial/navman.mod := printf '%s\n'   navman.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/navman.mod
