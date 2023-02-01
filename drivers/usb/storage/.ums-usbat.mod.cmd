cmd_drivers/usb/storage/ums-usbat.mod := printf '%s\n'   shuttle_usbat.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-usbat.mod
