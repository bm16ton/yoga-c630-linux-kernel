cmd_net/netfilter/xt_physdev.mod := printf '%s\n'   xt_physdev.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_physdev.mod
