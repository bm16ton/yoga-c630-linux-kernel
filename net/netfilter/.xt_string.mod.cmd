cmd_net/netfilter/xt_string.mod := printf '%s\n'   xt_string.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_string.mod
