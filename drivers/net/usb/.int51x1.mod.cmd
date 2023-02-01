cmd_drivers/net/usb/int51x1.mod := printf '%s\n'   int51x1.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/int51x1.mod
