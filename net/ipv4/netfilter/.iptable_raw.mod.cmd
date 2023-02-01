cmd_net/ipv4/netfilter/iptable_raw.mod := printf '%s\n'   iptable_raw.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/iptable_raw.mod
