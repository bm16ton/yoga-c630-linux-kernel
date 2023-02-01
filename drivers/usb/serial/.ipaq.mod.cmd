cmd_drivers/usb/serial/ipaq.mod := printf '%s\n'   ipaq.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ipaq.mod
