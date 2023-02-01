cmd_drivers/net/usb/smsc95xx.mod := printf '%s\n'   smsc95xx.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/smsc95xx.mod
