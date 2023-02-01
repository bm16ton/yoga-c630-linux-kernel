cmd_drivers/usb/misc/ftdi-elan.mod := printf '%s\n'   ftdi-elan.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/ftdi-elan.mod
