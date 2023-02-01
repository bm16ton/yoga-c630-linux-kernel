cmd_net/netfilter/xt_tcpudp.mod := printf '%s\n'   xt_tcpudp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_tcpudp.mod
