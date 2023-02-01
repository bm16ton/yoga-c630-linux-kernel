cmd_net/bluetooth/bnep/bnep.mod := printf '%s\n'   core.o sock.o netdev.o | awk '!x[$$0]++ { print("net/bluetooth/bnep/"$$0) }' > net/bluetooth/bnep/bnep.mod
