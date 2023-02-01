cmd_drivers/usb/serial/metro-usb.mod := printf '%s\n'   metro-usb.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/metro-usb.mod
