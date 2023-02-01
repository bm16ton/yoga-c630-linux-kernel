cmd_drivers/media/usb/siano/smsusb.mod := printf '%s\n'   smsusb.o | awk '!x[$$0]++ { print("drivers/media/usb/siano/"$$0) }' > drivers/media/usb/siano/smsusb.mod
