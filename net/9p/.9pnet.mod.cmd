cmd_net/9p/9pnet.mod := printf '%s\n'   mod.o client.o error.o protocol.o trans_common.o | awk '!x[$$0]++ { print("net/9p/"$$0) }' > net/9p/9pnet.mod
