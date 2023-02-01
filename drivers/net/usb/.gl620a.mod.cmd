cmd_drivers/net/usb/gl620a.mod := printf '%s\n'   gl620a.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/gl620a.mod
