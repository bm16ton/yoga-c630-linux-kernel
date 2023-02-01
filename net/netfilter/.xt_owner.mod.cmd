cmd_net/netfilter/xt_owner.mod := printf '%s\n'   xt_owner.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_owner.mod
