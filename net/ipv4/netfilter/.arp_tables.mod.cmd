cmd_net/ipv4/netfilter/arp_tables.mod := printf '%s\n'   arp_tables.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/arp_tables.mod
