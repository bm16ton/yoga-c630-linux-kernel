cmd_net/netfilter/xt_MASQUERADE.mod := printf '%s\n'   xt_MASQUERADE.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_MASQUERADE.mod
