cmd_net/netfilter/xt_AUDIT.mod := printf '%s\n'   xt_AUDIT.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_AUDIT.mod
