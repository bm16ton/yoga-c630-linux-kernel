cmd_drivers/net/usb/ipheth.mod := printf '%s\n'   ipheth.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/ipheth.mod
