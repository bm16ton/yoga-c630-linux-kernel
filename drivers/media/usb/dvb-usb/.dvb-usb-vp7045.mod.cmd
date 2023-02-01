cmd_drivers/media/usb/dvb-usb/dvb-usb-vp7045.mod := printf '%s\n'   vp7045.o vp7045-fe.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-vp7045.mod
