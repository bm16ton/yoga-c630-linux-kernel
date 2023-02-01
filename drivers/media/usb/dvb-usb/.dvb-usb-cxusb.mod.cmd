cmd_drivers/media/usb/dvb-usb/dvb-usb-cxusb.mod := printf '%s\n'   cxusb.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-cxusb.mod
