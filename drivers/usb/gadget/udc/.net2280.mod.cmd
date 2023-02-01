cmd_drivers/usb/gadget/udc/net2280.mod := printf '%s\n'   net2280.o | awk '!x[$$0]++ { print("drivers/usb/gadget/udc/"$$0) }' > drivers/usb/gadget/udc/net2280.mod
