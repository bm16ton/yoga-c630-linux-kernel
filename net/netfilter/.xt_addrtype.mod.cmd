cmd_net/netfilter/xt_addrtype.mod := printf '%s\n'   xt_addrtype.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_addrtype.mod
