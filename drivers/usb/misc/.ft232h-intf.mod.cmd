cmd_drivers/usb/misc/ft232h-intf.mod := printf '%s\n'   ft232h-intf.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/ft232h-intf.mod
