cmd_drivers/usb/gadget/function/usb_f_eem.mod := printf '%s\n'   f_eem.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_eem.mod
