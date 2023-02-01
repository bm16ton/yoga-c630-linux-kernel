cmd_drivers/net/usb/usbnet.mod := printf '%s\n'   usbnet.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/usbnet.mod
