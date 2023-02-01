cmd_net/netfilter/xt_quota.mod := printf '%s\n'   xt_quota.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_quota.mod
