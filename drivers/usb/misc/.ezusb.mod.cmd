cmd_drivers/usb/misc/ezusb.mod := printf '%s\n'   ezusb.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/ezusb.mod
