cmd_drivers/usb/gadget/function/usb_f_rndis.mod := printf '%s\n'   f_rndis.o rndis.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_rndis.mod
