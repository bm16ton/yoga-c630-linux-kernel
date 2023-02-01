cmd_drivers/net/usb/dm9601.mod := printf '%s\n'   dm9601.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/dm9601.mod
