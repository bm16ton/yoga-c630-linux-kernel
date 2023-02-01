cmd_drivers/usb/gadget/legacy/g_nokia.mod := printf '%s\n'   nokia.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_nokia.mod
