cmd_net/netfilter/xt_dscp.mod := printf '%s\n'   xt_dscp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_dscp.mod
