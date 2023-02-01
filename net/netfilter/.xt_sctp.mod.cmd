cmd_net/netfilter/xt_sctp.mod := printf '%s\n'   xt_sctp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_sctp.mod
