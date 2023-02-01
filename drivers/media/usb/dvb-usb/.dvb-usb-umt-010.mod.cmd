cmd_drivers/media/usb/dvb-usb/dvb-usb-umt-010.mod := printf '%s\n'   umt-010.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-umt-010.mod
