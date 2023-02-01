cmd_drivers/usb/serial/cyberjack.mod := printf '%s\n'   cyberjack.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/cyberjack.mod
