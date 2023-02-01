cmd_net/netfilter/xt_mac.mod := printf '%s\n'   xt_mac.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_mac.mod
