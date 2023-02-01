cmd_net/ipv4/netfilter/arptable_filter.mod := printf '%s\n'   arptable_filter.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/arptable_filter.mod
