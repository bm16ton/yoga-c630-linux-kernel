cmd_drivers/usb/storage/ums-alauda.mod := printf '%s\n'   alauda.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-alauda.mod
