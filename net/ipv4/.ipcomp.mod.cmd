cmd_net/ipv4/ipcomp.mod := printf '%s\n'   ipcomp.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/ipcomp.mod
