cmd_drivers/net/can/usb/mcba_usb.mod := printf '%s\n'   mcba_usb.o | awk '!x[$$0]++ { print("drivers/net/can/usb/"$$0) }' > drivers/net/can/usb/mcba_usb.mod
