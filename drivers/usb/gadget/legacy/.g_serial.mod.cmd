cmd_drivers/usb/gadget/legacy/g_serial.mod := printf '%s\n'   serial.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_serial.mod
