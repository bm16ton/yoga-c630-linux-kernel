cmd_net/netfilter/nf_nat_tftp.mod := printf '%s\n'   nf_nat_tftp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_nat_tftp.mod
