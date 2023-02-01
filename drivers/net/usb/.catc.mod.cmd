cmd_drivers/net/usb/catc.mod := printf '%s\n'   catc.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/catc.mod
