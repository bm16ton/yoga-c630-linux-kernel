cmd_drivers/usb/gadget/function/usb_f_uac2.mod := printf '%s\n'   f_uac2.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_uac2.mod
