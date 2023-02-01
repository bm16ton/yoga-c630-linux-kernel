cmd_net/netfilter/xt_NFQUEUE.mod := printf '%s\n'   xt_NFQUEUE.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_NFQUEUE.mod
