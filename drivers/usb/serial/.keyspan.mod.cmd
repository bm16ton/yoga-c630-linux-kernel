cmd_drivers/usb/serial/keyspan.mod := printf '%s\n'   keyspan.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/keyspan.mod
