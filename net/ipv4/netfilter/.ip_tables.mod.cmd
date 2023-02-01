cmd_net/ipv4/netfilter/ip_tables.mod := printf '%s\n'   ip_tables.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/ip_tables.mod
