cmd_net/netfilter/xt_policy.mod := printf '%s\n'   xt_policy.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_policy.mod
