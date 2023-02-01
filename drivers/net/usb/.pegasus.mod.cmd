cmd_drivers/net/usb/pegasus.mod := printf '%s\n'   pegasus.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/pegasus.mod
