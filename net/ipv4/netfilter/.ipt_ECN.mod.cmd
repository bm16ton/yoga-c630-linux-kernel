cmd_net/ipv4/netfilter/ipt_ECN.mod := printf '%s\n'   ipt_ECN.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/ipt_ECN.mod
