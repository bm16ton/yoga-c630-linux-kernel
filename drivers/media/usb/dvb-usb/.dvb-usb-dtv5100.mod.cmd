cmd_drivers/media/usb/dvb-usb/dvb-usb-dtv5100.mod := printf '%s\n'   dtv5100.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-dtv5100.mod
