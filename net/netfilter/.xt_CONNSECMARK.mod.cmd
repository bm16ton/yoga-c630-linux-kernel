cmd_net/netfilter/xt_CONNSECMARK.mod := printf '%s\n'   xt_CONNSECMARK.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_CONNSECMARK.mod
