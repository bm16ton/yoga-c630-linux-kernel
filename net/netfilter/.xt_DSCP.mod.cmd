cmd_net/netfilter/xt_DSCP.mod := printf '%s\n'   xt_DSCP.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_DSCP.mod
