cmd_net/ipv6/netfilter/nf_defrag_ipv6.mod := printf '%s\n'   nf_defrag_ipv6_hooks.o nf_conntrack_reasm.o | awk '!x[$$0]++ { print("net/ipv6/netfilter/"$$0) }' > net/ipv6/netfilter/nf_defrag_ipv6.mod
