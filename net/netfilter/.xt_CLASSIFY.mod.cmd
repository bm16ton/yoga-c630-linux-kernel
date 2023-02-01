cmd_net/netfilter/xt_CLASSIFY.mod := printf '%s\n'   xt_CLASSIFY.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_CLASSIFY.mod
