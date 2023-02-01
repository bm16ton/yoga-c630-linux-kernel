cmd_net/netfilter/xt_pkttype.mod := printf '%s\n'   xt_pkttype.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_pkttype.mod
