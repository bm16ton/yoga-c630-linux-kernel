cmd_drivers/usb/serial/mct_u232.mod := printf '%s\n'   mct_u232.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/mct_u232.mod
