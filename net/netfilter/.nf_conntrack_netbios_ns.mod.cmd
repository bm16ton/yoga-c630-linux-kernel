cmd_net/netfilter/nf_conntrack_netbios_ns.mod := printf '%s\n'   nf_conntrack_netbios_ns.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_conntrack_netbios_ns.mod
