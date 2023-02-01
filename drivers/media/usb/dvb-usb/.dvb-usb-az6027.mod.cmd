cmd_drivers/media/usb/dvb-usb/dvb-usb-az6027.mod := printf '%s\n'   az6027.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb/"$$0) }' > drivers/media/usb/dvb-usb/dvb-usb-az6027.mod
