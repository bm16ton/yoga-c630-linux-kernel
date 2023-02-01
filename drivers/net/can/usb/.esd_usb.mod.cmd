cmd_drivers/net/can/usb/esd_usb.mod := printf '%s\n'   esd_usb.o | awk '!x[$$0]++ { print("drivers/net/can/usb/"$$0) }' > drivers/net/can/usb/esd_usb.mod
