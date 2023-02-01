cmd_drivers/net/usb/lg-vl600.mod := printf '%s\n'   lg-vl600.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/lg-vl600.mod
