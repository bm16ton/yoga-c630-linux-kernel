cmd_net/ipv4/tunnel4.mod := printf '%s\n'   tunnel4.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/tunnel4.mod
