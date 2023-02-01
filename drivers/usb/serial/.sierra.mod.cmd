cmd_drivers/usb/serial/sierra.mod := printf '%s\n'   sierra.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/sierra.mod
