cmd_drivers/usb/serial/cp210x.mod := printf '%s\n'   cp210x.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/cp210x.mod
