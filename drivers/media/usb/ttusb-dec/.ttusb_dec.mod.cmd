cmd_drivers/media/usb/ttusb-dec/ttusb_dec.mod := printf '%s\n'   ttusb_dec.o | awk '!x[$$0]++ { print("drivers/media/usb/ttusb-dec/"$$0) }' > drivers/media/usb/ttusb-dec/ttusb_dec.mod
