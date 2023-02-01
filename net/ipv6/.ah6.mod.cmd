cmd_net/ipv6/ah6.mod := printf '%s\n'   ah6.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/ah6.mod
