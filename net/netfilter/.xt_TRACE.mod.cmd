cmd_net/netfilter/xt_TRACE.mod := printf '%s\n'   xt_TRACE.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_TRACE.mod
