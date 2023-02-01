cmd_drivers/usb/class/cdc-acm.mod := printf '%s\n'   cdc-acm.o | awk '!x[$$0]++ { print("drivers/usb/class/"$$0) }' > drivers/usb/class/cdc-acm.mod
