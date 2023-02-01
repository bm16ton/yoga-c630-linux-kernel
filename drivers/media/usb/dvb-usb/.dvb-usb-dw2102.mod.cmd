cmd_drivers/media/usb/dvb-usb/dvb-usb-dw2102.mod := printf '%s\n'   dw2102.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-dw2102.mod
