cmd_drivers/usb/image/mdc800.mod := printf '%s\n'   mdc800.o | awk '!x[$$0]++ { print("drivers/usb/image/"$$0) }' > drivers/usb/image/mdc800.mod
