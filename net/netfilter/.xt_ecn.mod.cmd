cmd_net/netfilter/xt_ecn.mod := printf '%s\n'   xt_ecn.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_ecn.mod
