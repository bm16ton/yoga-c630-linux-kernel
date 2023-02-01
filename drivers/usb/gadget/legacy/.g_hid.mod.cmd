cmd_drivers/usb/gadget/legacy/g_hid.mod := printf '%s\n'   hid.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_hid.mod
