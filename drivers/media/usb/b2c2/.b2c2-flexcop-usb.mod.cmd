cmd_drivers/media/usb/b2c2/b2c2-flexcop-usb.mod := printf '%s\n'   flexcop-usb.o | awk '!x[$$0]++ { print("drivers/media/usb/b2c2/"$$0) }' > drivers/media/usb/b2c2/b2c2-flexcop-usb.mod
