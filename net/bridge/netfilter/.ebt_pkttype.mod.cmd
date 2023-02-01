cmd_net/bridge/netfilter/ebt_pkttype.mod := printf '%s\n'   ebt_pkttype.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_pkttype.mod
