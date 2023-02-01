cmd_drivers/media/usb/dvb-usb/dvb-usb-vp702x.mod := printf '%s\n'   vp702x.o vp702x-fe.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-vp702x.mod
