cmd_drivers/media/usb/dvb-usb-v2/zd1301.mod := printf '%s\n'   zd1301.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/zd1301.mod
