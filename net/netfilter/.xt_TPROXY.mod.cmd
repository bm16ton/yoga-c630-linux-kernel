cmd_net/netfilter/xt_TPROXY.mod := printf '%s\n'   xt_TPROXY.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_TPROXY.mod
