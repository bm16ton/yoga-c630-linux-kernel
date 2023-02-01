cmd_drivers/usb/typec/stusb160x.mod := printf '%s\n'   stusb160x.o | awk '!x[$$0]++ { print("drivers/usb/typec/"$$0) }' > drivers/usb/typec/stusb160x.mod
