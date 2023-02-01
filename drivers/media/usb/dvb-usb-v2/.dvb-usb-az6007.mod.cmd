cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-az6007.mod := printf '%s\n'   az6007.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-az6007.mod
