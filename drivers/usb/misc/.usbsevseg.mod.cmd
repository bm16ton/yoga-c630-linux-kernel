cmd_drivers/usb/misc/usbsevseg.mod := printf '%s\n'   usbsevseg.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/usbsevseg.mod
