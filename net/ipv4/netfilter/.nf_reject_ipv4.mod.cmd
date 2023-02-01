cmd_net/ipv4/netfilter/nf_reject_ipv4.mod := printf '%s\n'   nf_reject_ipv4.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/nf_reject_ipv4.mod
