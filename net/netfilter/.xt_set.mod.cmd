cmd_net/netfilter/xt_set.mod := printf '%s\n'   xt_set.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_set.mod
