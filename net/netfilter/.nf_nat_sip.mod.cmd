cmd_net/netfilter/nf_nat_sip.mod := printf '%s\n'   nf_nat_sip.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_nat_sip.mod
