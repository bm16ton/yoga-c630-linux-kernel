cmd_net/netfilter/xt_LOG.mod := printf '%s\n'   xt_LOG.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_LOG.mod
