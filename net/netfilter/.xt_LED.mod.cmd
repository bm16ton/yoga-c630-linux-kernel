cmd_net/netfilter/xt_LED.mod := printf '%s\n'   xt_LED.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_LED.mod
