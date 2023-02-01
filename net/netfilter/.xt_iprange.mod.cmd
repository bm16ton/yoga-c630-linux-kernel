cmd_net/netfilter/xt_iprange.mod := printf '%s\n'   xt_iprange.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_iprange.mod
