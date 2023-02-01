cmd_drivers/media/usb/cx231xx/cx231xx-dvb.mod := printf '%s\n'   cx231xx-dvb.o | awk '!x[$$0]++ { print("drivers/media/usb/cx231xx/"$$0) }' > drivers/media/usb/cx231xx/cx231xx-dvb.mod
