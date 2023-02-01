cmd_net/netfilter/xt_recent.mod := printf '%s\n'   xt_recent.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_recent.mod
