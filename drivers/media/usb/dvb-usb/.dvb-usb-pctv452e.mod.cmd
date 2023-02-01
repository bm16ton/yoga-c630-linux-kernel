cmd_drivers/media/usb/dvb-usb/dvb-usb-pctv452e.mod := printf '%s\n'   pctv452e.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-pctv452e.mod
