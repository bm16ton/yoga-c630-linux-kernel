cmd_drivers/bluetooth/bfusb.mod := printf '%s\n'   bfusb.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/bfusb.mod
