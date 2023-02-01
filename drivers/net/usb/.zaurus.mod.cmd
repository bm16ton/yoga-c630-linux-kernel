cmd_drivers/net/usb/zaurus.mod := printf '%s\n'   zaurus.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/zaurus.mod
