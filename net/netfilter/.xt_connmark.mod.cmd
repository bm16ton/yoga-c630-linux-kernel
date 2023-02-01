cmd_net/netfilter/xt_connmark.mod := printf '%s\n'   xt_connmark.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_connmark.mod
