cmd_net/netfilter/nf_dup_netdev.mod := printf '%s\n'   nf_dup_netdev.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_dup_netdev.mod
