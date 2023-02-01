cmd_drivers/net/usb/sr9700.mod := printf '%s\n'   sr9700.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/sr9700.mod
