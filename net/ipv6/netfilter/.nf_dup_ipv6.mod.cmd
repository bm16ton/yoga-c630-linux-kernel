cmd_net/ipv6/netfilter/nf_dup_ipv6.mod := printf '%s\n'   nf_dup_ipv6.o | awk '!x[$$0]++ { print("net/ipv6/netfilter/"$$0) }' > net/ipv6/netfilter/nf_dup_ipv6.mod
