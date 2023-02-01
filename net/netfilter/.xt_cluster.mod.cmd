cmd_net/netfilter/xt_cluster.mod := printf '%s\n'   xt_cluster.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_cluster.mod
