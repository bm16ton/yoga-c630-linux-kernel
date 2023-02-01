cmd_net/netfilter/xt_l2tp.mod := printf '%s\n'   xt_l2tp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_l2tp.mod
