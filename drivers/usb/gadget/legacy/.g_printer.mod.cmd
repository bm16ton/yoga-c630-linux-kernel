cmd_drivers/usb/gadget/legacy/g_printer.mod := printf '%s\n'   printer.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_printer.mod
