cmd_net/ipv6/fou6.mod := printf '%s\n'   fou6.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/fou6.mod
