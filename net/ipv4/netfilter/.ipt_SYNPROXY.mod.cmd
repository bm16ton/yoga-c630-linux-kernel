cmd_net/ipv4/netfilter/ipt_SYNPROXY.mod := printf '%s\n'   ipt_SYNPROXY.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/ipt_SYNPROXY.mod
