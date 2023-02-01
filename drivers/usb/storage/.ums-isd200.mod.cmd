cmd_drivers/usb/storage/ums-isd200.mod := printf '%s\n'   isd200.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-isd200.mod
