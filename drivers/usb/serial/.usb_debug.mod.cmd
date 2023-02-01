cmd_drivers/usb/serial/usb_debug.mod := printf '%s\n'   usb_debug.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/usb_debug.mod
