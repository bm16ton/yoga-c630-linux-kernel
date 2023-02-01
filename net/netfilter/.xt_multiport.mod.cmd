cmd_net/netfilter/xt_multiport.mod := printf '%s\n'   xt_multiport.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_multiport.mod
