cmd_drivers/usb/serial/io_edgeport.mod := printf '%s\n'   io_edgeport.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/io_edgeport.mod
