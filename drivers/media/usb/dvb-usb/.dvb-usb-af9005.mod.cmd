cmd_drivers/media/usb/dvb-usb/dvb-usb-af9005.mod := printf '%s\n'   af9005.o af9005-fe.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-af9005.mod
