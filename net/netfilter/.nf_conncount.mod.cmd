cmd_net/netfilter/nf_conncount.mod := printf '%s\n'   nf_conncount.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_conncount.mod
