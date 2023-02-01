cmd_net/netfilter/xt_connbytes.mod := printf '%s\n'   xt_connbytes.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_connbytes.mod
