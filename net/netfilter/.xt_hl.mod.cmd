cmd_net/netfilter/xt_hl.mod := printf '%s\n'   xt_hl.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_hl.mod
