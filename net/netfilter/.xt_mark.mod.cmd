cmd_net/netfilter/xt_mark.mod := printf '%s\n'   xt_mark.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_mark.mod
