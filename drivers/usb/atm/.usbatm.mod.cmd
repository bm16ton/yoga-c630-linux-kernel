cmd_drivers/usb/atm/usbatm.mod := printf '%s\n'   usbatm.o | awk '!x[$$0]++ { print("drivers/usb/atm/"$$0) }' > drivers/usb/atm/usbatm.mod
