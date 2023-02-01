cmd_net/ipv4/netfilter/ipt_ah.mod := printf '%s\n'   ipt_ah.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/ipt_ah.mod
