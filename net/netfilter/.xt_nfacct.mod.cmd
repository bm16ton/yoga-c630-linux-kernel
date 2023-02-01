cmd_net/netfilter/xt_nfacct.mod := printf '%s\n'   xt_nfacct.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_nfacct.mod
