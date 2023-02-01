cmd_net/ipv4/netfilter/nf_nat_h323.mod := printf '%s\n'   nf_nat_h323.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/nf_nat_h323.mod
