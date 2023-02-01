cmd_net/netfilter/xt_devgroup.mod := printf '%s\n'   xt_devgroup.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_devgroup.mod
