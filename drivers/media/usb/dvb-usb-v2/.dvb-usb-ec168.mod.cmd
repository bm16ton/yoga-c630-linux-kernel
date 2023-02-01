cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-ec168.mod := printf '%s\n'   ec168.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-ec168.mod
