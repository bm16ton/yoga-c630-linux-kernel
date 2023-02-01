cmd_net/netfilter/xt_ipcomp.mod := printf '%s\n'   xt_ipcomp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_ipcomp.mod
