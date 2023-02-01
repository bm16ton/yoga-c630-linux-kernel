cmd_net/netfilter/nf_nat_irc.mod := printf '%s\n'   nf_nat_irc.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_nat_irc.mod
