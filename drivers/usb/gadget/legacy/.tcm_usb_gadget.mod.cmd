cmd_drivers/usb/gadget/legacy/tcm_usb_gadget.mod := printf '%s\n'   tcm_usb_gadget.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/tcm_usb_gadget.mod
