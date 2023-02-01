cmd_drivers/usb/gadget/function/u_serial.mod := printf '%s\n'   u_serial.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/u_serial.mod
