cmd_net/netfilter/xt_HMARK.mod := printf '%s\n'   xt_HMARK.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_HMARK.mod
