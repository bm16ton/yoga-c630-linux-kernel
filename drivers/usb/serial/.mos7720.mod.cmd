cmd_drivers/usb/serial/mos7720.mod := printf '%s\n'   mos7720.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/mos7720.mod
