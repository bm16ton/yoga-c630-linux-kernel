cmd_net/netfilter/xt_limit.mod := printf '%s\n'   xt_limit.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_limit.mod
