cmd_net/netfilter/xt_tcpmss.mod := printf '%s\n'   xt_tcpmss.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_tcpmss.mod
