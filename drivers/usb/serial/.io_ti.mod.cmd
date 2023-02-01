cmd_drivers/usb/serial/io_ti.mod := printf '%s\n'   io_ti.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/io_ti.mod
