cmd_drivers/usb/serial/digi_acceleport.mod := printf '%s\n'   digi_acceleport.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/digi_acceleport.mod
