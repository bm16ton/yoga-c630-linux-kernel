cmd_drivers/media/usb/dvb-usb/dvb-usb-a800.mod := printf '%s\n'   a800.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-a800.mod
