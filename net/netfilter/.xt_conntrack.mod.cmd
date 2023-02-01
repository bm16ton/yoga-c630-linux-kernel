cmd_net/netfilter/xt_conntrack.mod := printf '%s\n'   xt_conntrack.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_conntrack.mod
