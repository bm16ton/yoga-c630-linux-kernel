cmd_net/ipv6/sit.mod := printf '%s\n'   sit.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/sit.mod
