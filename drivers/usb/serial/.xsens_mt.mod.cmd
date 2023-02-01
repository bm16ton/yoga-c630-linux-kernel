cmd_drivers/usb/serial/xsens_mt.mod := printf '%s\n'   xsens_mt.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/xsens_mt.mod
