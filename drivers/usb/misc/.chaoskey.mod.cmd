cmd_drivers/usb/misc/chaoskey.mod := printf '%s\n'   chaoskey.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/chaoskey.mod
