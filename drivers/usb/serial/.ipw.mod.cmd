cmd_drivers/usb/serial/ipw.mod := printf '%s\n'   ipw.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ipw.mod
