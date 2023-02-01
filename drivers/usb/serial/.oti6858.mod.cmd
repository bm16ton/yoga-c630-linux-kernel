cmd_drivers/usb/serial/oti6858.mod := printf '%s\n'   oti6858.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/oti6858.mod
