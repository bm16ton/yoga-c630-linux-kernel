cmd_drivers/usb/gadget/legacy/g_ether.mod := printf '%s\n'   ether.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_ether.mod
