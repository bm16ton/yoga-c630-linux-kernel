cmd_net/netfilter/xt_u32.mod := printf '%s\n'   xt_u32.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_u32.mod
