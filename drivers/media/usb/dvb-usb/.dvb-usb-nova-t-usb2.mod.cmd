cmd_drivers/media/usb/dvb-usb/dvb-usb-nova-t-usb2.mod := printf '%s\n'   nova-t-usb2.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-nova-t-usb2.mod
