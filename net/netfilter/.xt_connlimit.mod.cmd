cmd_net/netfilter/xt_connlimit.mod := printf '%s\n'   xt_connlimit.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_connlimit.mod
