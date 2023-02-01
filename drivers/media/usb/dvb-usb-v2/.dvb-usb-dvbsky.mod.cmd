cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-dvbsky.mod := printf '%s\n'   dvbsky.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-dvbsky.mod
