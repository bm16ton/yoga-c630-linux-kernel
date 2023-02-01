cmd_drivers/media/usb/ttusb-dec/ttusbdecfe.mod := printf '%s\n'   ttusbdecfe.o | awk '!x[$$0]++ { print("drivers/media/usb/ttusb-dec/"$$0) }' > drivers/media/usb/ttusb-dec/ttusbdecfe.mod
