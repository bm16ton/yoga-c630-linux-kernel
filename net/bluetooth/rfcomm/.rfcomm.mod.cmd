cmd_net/bluetooth/rfcomm/rfcomm.mod := printf '%s\n'   core.o sock.o tty.o | awk '!x[$$0]++ { print("net/bluetooth/rfcomm/"$$0) }' > net/bluetooth/rfcomm/rfcomm.mod
