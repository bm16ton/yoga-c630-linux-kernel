cmd_drivers/net/can/usb/ucan.mod := printf '%s\n'   ucan.o | awk '!x[$$0]++ { print("drivers/net/can/usb/"$$0) }' > drivers/net/can/usb/ucan.mod
