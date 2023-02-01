cmd_drivers/usb/gadget/legacy/g_multi.mod := printf '%s\n'   multi.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_multi.mod
