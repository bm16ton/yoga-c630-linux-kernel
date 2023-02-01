cmd_drivers/usb/storage/ums-onetouch.mod := printf '%s\n'   onetouch.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-onetouch.mod
