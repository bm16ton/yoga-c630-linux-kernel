cmd_net/ipv4/netfilter/ipt_rpfilter.mod := printf '%s\n'   ipt_rpfilter.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/ipt_rpfilter.mod
