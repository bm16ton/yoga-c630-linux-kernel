cmd_drivers/usb/gadget/function/usb_f_ncm.mod := printf '%s\n'   f_ncm.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_ncm.mod
