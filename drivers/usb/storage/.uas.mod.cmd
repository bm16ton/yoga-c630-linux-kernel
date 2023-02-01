cmd_drivers/usb/storage/uas.mod := printf '%s\n'   uas.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/uas.mod
