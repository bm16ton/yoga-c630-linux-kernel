cmd_drivers/net/can/usb/ems_usb.mod := printf '%s\n'   ems_usb.o | awk '!x[$$0]++ { print("drivers/net/can/usb/"$$0) }' > drivers/net/can/usb/ems_usb.mod
