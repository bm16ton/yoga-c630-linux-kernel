cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-lmedm04.mod := printf '%s\n'   lmedm04.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-lmedm04.mod
