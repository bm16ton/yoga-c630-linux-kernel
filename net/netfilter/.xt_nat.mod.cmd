cmd_net/netfilter/xt_nat.mod := printf '%s\n'   xt_nat.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_nat.mod
