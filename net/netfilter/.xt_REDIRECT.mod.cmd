cmd_net/netfilter/xt_REDIRECT.mod := printf '%s\n'   xt_REDIRECT.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_REDIRECT.mod
