cmd_drivers/net/usb/lan78xx.mod := printf '%s\n'   lan78xx.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/lan78xx.mod
