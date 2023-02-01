cmd_drivers/usb/misc/usb3503.mod := printf '%s\n'   usb3503.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/usb3503.mod
