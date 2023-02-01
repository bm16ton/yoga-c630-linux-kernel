cmd_drivers/nfc/pn533/pn533_usb.mod := printf '%s\n'   usb.o | awk '!x[$$0]++ { print("drivers/nfc/pn533/"$$0) }' > drivers/nfc/pn533/pn533_usb.mod
