cmd_net/bluetooth/bluetooth_6lowpan.mod := printf '%s\n'   6lowpan.o | awk '!x[$$0]++ { print("net/bluetooth/"$$0) }' > net/bluetooth/bluetooth_6lowpan.mod
