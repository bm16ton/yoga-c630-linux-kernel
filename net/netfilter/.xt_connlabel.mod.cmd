cmd_net/netfilter/xt_connlabel.mod := printf '%s\n'   xt_connlabel.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_connlabel.mod
