cmd_drivers/usb/storage/ums-datafab.mod := printf '%s\n'   datafab.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-datafab.mod
