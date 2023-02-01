cmd_drivers/media/usb/dvb-usb-v2/dvb-usb-rtl28xxu.mod := printf '%s\n'   rtl28xxu.o | awk '!x[$$0]++ { print("drivers/media/usb/dvb-usb-v2/"$$0) }' > drivers/media/usb/dvb-usb-v2/dvb-usb-rtl28xxu.mod
