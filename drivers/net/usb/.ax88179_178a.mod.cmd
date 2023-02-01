cmd_drivers/net/usb/ax88179_178a.mod := printf '%s\n'   ax88179_178a.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/ax88179_178a.mod
