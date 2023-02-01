cmd_drivers/usb/serial/ark3116.mod := printf '%s\n'   ark3116.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ark3116.mod
