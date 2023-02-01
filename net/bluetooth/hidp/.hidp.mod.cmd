cmd_net/bluetooth/hidp/hidp.mod := printf '%s\n'   core.o sock.o | awk '!x[$$0]++ { print("net/bluetooth/hidp/"$$0) }' > net/bluetooth/hidp/hidp.mod
