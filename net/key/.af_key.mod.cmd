cmd_net/key/af_key.mod := printf '%s\n'   af_key.o | awk '!x[$$0]++ { print("net/key/"$$0) }' > net/key/af_key.mod
