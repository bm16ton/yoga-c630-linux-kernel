cmd_drivers/net/can/usb/gs_usb.mod := printf '%s\n'   gs_usb.o | awk '!x[$$0]++ { print("drivers/net/can/usb/"$$0) }' > drivers/net/can/usb/gs_usb.mod
