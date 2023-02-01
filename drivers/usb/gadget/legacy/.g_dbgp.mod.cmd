cmd_drivers/usb/gadget/legacy/g_dbgp.mod := printf '%s\n'   dbgp.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_dbgp.mod
