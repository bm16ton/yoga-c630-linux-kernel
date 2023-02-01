cmd_drivers/usb/gadget/function/usb_f_midi.mod := printf '%s\n'   f_midi.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/usb_f_midi.mod
