cmd_drivers/bluetooth/btusb.mod := printf '%s\n'   btusb.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btusb.mod
