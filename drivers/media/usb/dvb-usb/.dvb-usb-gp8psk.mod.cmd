cmd_drivers/media/usb/dvb-usb/dvb-usb-gp8psk.mod := printf '%s\n'   gp8psk.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-gp8psk.mod
