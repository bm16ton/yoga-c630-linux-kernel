cmd_net/netfilter/xt_TCPOPTSTRIP.mod := printf '%s\n'   xt_TCPOPTSTRIP.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_TCPOPTSTRIP.mod
