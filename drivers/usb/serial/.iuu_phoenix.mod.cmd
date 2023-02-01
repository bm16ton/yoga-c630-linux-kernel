cmd_drivers/usb/serial/iuu_phoenix.mod := printf '%s\n'   iuu_phoenix.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/iuu_phoenix.mod
