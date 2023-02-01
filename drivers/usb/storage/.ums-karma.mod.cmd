cmd_drivers/usb/storage/ums-karma.mod := printf '%s\n'   karma.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-karma.mod
