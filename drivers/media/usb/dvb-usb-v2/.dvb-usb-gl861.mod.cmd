cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-gl861.mod := printf '%s\n'   gl861.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-gl861.mod
