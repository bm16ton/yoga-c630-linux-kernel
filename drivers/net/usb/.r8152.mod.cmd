cmd_drivers/net/usb/r8152.mod := printf '%s\n'   r8152.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/r8152.mod
