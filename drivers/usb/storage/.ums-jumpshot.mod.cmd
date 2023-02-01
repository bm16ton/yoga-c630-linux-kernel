cmd_drivers/usb/storage/ums-jumpshot.mod := printf '%s\n'   jumpshot.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-jumpshot.mod
