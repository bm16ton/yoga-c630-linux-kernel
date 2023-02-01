cmd_drivers/usb/gadget/function/usb_f_acm.mod := printf '%s\n'   f_acm.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_acm.mod
