cmd_drivers/usb/serial/ssu100.mod := printf '%s\n'   ssu100.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ssu100.mod
