cmd_net/netfilter/xt_time.mod := printf '%s\n'   xt_time.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_time.mod
