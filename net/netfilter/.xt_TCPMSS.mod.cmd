cmd_net/netfilter/xt_TCPMSS.mod := printf '%s\n'   xt_TCPMSS.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_TCPMSS.mod
