cmd_drivers/net/can/usb/usb_8dev.mod := printf '%s\n'   usb_8dev.o | awk '!x[$$0]++ { print("drivers/net/can/usb/"$$0) }' > drivers/net/can/usb/usb_8dev.mod
