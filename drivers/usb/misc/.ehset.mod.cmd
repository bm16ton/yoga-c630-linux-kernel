cmd_drivers/usb/misc/ehset.mod := printf '%s\n'   ehset.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/ehset.mod
