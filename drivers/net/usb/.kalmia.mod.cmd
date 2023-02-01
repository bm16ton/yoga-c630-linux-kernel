cmd_drivers/net/usb/kalmia.mod := printf '%s\n'   kalmia.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/kalmia.mod
