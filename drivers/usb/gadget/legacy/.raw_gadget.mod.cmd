cmd_drivers/usb/gadget/legacy/raw_gadget.mod := printf '%s\n'   raw_gadget.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/raw_gadget.mod
