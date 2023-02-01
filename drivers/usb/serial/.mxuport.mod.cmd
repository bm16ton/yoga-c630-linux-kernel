cmd_drivers/usb/serial/mxuport.mod := printf '%s\n'   mxuport.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/mxuport.mod
