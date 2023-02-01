cmd_drivers/usb/serial/usb_wwan.mod := printf '%s\n'   usb_wwan.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/usb_wwan.mod
