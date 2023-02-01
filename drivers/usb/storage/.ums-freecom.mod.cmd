cmd_drivers/usb/storage/ums-freecom.mod := printf '%s\n'   freecom.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-freecom.mod
