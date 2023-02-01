cmd_drivers/usb/storage/ums-sddr55.mod := printf '%s\n'   sddr55.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-sddr55.mod
