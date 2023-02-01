cmd_drivers/usb/misc/ldusb.mod := printf '%s\n'   ldusb.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/ldusb.mod
