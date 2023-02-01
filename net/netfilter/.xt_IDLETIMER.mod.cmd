cmd_net/netfilter/xt_IDLETIMER.mod := printf '%s\n'   xt_IDLETIMER.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_IDLETIMER.mod
