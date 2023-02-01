cmd_drivers/media/usb/dvb-usb/dvb-usb-digitv.mod := printf '%s\n'   digitv.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-digitv.mod
