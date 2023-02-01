cmd_drivers/net/usb/net1080.mod := printf '%s\n'   net1080.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/net1080.mod
