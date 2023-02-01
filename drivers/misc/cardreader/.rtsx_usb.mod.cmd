cmd_drivers/misc/cardreader/rtsx_usb.mod := printf '%s\n'   rtsx_usb.o | awk '!x[$$0]++ { print("drivers/misc/cardreader/"$$0) }' > drivers/misc/cardreader/rtsx_usb.mod
