cmd_drivers/net/usb/ch9200.mod := printf '%s\n'   ch9200.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/ch9200.mod
