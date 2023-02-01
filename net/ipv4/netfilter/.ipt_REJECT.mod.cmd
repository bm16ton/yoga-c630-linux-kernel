cmd_net/ipv4/netfilter/ipt_REJECT.mod := printf '%s\n'   ipt_REJECT.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/ipt_REJECT.mod
