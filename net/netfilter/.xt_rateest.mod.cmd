cmd_net/netfilter/xt_rateest.mod := printf '%s\n'   xt_rateest.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_rateest.mod
