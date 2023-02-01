cmd_net/ipv6/ipcomp6.mod := printf '%s\n'   ipcomp6.o | awk '!x[$$0]++ { print("net/ipv6/"$$0) }' > net/ipv6/ipcomp6.mod
