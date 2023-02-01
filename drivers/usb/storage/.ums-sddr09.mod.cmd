cmd_drivers/usb/storage/ums-sddr09.mod := printf '%s\n'   sddr09.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-sddr09.mod
