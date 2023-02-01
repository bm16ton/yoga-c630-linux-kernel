cmd_drivers/usb/serial/ir-usb.mod := printf '%s\n'   ir-usb.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ir-usb.mod
