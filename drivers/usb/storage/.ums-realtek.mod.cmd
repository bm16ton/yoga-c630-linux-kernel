cmd_drivers/usb/storage/ums-realtek.mod := printf '%s\n'   realtek_cr.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-realtek.mod
