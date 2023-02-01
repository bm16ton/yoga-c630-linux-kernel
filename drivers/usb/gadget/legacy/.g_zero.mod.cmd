cmd_drivers/usb/gadget/legacy/g_zero.mod := printf '%s\n'   zero.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_zero.mod
