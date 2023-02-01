cmd_drivers/usb/serial/usb-serial-simple.mod := printf '%s\n'   usb-serial-simple.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/usb-serial-simple.mod
