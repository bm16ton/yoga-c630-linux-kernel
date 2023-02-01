cmd_net/bridge/netfilter/ebt_arpreply.mod := printf '%s\n'   ebt_arpreply.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_arpreply.mod
