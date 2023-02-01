cmd_drivers/media/usb/dvb-usb/dvb-usb-dibusb-mb.mod := printf '%s\n'   dibusb-mb.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-dibusb-mb.mod
