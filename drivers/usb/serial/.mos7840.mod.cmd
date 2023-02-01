cmd_drivers/usb/serial/mos7840.mod := printf '%s\n'   mos7840.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/mos7840.mod
