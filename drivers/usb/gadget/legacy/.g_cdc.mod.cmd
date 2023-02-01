cmd_drivers/usb/gadget/legacy/g_cdc.mod := printf '%s\n'   cdc2.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_cdc.mod
