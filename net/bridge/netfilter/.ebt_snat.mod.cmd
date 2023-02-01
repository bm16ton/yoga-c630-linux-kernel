cmd_net/bridge/netfilter/ebt_snat.mod := printf '%s\n'   ebt_snat.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_snat.mod
