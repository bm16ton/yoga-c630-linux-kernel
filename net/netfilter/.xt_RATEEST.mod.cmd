cmd_net/netfilter/xt_RATEEST.mod := printf '%s\n'   xt_RATEEST.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_RATEEST.mod
