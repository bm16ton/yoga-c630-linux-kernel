cmd_net/netfilter/xt_CT.mod := printf '%s\n'   xt_CT.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_CT.mod
