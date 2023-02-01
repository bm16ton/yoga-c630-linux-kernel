cmd_drivers/usb/typec/rt1719.mod := printf '%s\n'   rt1719.o | awk '!x[$$0]++ { print("drivers/usb/typec/"$$0) }' > drivers/usb/typec/rt1719.mod
