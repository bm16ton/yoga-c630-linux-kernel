cmd_net/netfilter/xt_esp.mod := printf '%s\n'   xt_esp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_esp.mod
