cmd_net/ipv4/netfilter/iptable_filter.mod := printf '%s\n'   iptable_filter.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/iptable_filter.mod
