cmd_drivers/usb/misc/usbtest.mod := printf '%s\n'   usbtest.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/usbtest.mod
