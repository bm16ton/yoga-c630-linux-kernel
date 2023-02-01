cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-af9035.mod := printf '%s\n'   af9035.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-af9035.mod
