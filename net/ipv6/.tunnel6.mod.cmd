cmd_net/ipv6/tunnel6.mod := printf '%s\n'   tunnel6.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/tunnel6.mod
