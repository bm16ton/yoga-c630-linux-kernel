cmd_net/netfilter/xt_length.mod := printf '%s\n'   xt_length.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_length.mod
