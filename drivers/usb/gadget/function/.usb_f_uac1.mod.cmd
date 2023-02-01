cmd_drivers/usb/gadget/function/usb_f_uac1.mod := printf '%s\n'   f_uac1.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_uac1.mod
