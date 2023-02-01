cmd_drivers/usb/misc/adutux.mod := printf '%s\n'   adutux.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/adutux.mod
