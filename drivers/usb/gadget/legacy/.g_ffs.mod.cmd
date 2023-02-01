cmd_drivers/usb/gadget/legacy/g_ffs.mod := printf '%s\n'   g_ffs.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_ffs.mod
