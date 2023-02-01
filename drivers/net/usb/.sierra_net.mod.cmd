cmd_drivers/net/usb/sierra_net.mod := printf '%s\n'   sierra_net.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/sierra_net.mod
