cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-au6610.mod := printf '%s\n'   au6610.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-au6610.mod
