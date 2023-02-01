cmd_drivers/usb/serial/omninet.mod := printf '%s\n'   omninet.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/omninet.mod
