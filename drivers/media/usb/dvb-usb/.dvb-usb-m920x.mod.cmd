cmd_drivers/media/usb/dvb-usb/dvb-usb-m920x.mod := printf '%s\n'   m920x.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-m920x.mod
