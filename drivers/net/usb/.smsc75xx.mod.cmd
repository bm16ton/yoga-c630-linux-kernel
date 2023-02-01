cmd_drivers/net/usb/smsc75xx.mod := printf '%s\n'   smsc75xx.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/smsc75xx.mod
