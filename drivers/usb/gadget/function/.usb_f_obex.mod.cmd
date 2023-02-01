cmd_drivers/usb/gadget/function/usb_f_obex.mod := printf '%s\n'   f_obex.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_obex.mod
