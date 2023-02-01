cmd_net/netfilter/nf_nat_amanda.mod := printf '%s\n'   nf_nat_amanda.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_nat_amanda.mod
