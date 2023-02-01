cmd_drivers/media/usb/dvb-usb/dvb-usb-opera.mod := printf '%s\n'   opera1.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-opera.mod
