cmd_drivers/net/usb/kaweth.mod := printf '%s\n'   kaweth.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/kaweth.mod
