cmd_drivers/usb/gadget/legacy/g_ncm.mod := printf '%s\n'   ncm.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_ncm.mod
