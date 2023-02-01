cmd_drivers/net/usb/rtl8150.mod := printf '%s\n'   rtl8150.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/rtl8150.mod
