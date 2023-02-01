cmd_net/ipv6/esp6.mod := printf '%s\n'   esp6.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/esp6.mod
