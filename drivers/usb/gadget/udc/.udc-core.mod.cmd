cmd_drivers/usb/gadget/udc/udc-core.mod := printf '%s\n'   core.o trace.o | awk '!x[$$0]++ { print("drivers/usb/gadget/udc/"$$0) }' > drivers/usb/gadget/udc/udc-core.mod
