cmd_drivers/net/usb/hso.mod := printf '%s\n'   hso.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/hso.mod
