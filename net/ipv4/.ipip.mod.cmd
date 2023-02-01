cmd_net/ipv4/ipip.mod := printf '%s\n'   ipip.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/ipip.mod
