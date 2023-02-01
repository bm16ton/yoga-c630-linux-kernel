cmd_drivers/usb/typec/wusb3801.mod := printf '%s\n'   wusb3801.o | awk '!x[$$0]++ { print("drivers/usb/typec/"$$0) }' > drivers/usb/typec/wusb3801.mod
