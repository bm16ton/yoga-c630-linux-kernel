cmd_drivers/media/usb/dvb-usb/dvb-usb-ttusb2.mod := printf '%s\n'   ttusb2.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-ttusb2.mod
