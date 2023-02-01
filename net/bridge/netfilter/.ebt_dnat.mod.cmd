cmd_net/bridge/netfilter/ebt_dnat.mod := printf '%s\n'   ebt_dnat.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_dnat.mod
