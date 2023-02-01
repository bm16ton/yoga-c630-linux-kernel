cmd_drivers/net/usb/mcs7830.mod := printf '%s\n'   mcs7830.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/mcs7830.mod
