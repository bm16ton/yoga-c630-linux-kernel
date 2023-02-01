cmd_net/netfilter/xt_dccp.mod := printf '%s\n'   xt_dccp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_dccp.mod
