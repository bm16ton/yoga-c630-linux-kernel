cmd_drivers/usb/gadget/function/usb_f_ecm_subset.mod := printf '%s\n'   f_subset.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_ecm_subset.mod
