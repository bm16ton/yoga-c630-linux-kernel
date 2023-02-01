cmd_drivers/usb/serial/option.mod := printf '%s\n'   option.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/option.mod
