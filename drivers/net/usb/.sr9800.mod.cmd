cmd_drivers/net/usb/sr9800.mod := printf '%s\n'   sr9800.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/sr9800.mod
