cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-af9015.mod := printf '%s\n'   af9015.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-af9015.mod
