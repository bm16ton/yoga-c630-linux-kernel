cmd_drivers/net/usb/plusb.mod := printf '%s\n'   plusb.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/plusb.mod
