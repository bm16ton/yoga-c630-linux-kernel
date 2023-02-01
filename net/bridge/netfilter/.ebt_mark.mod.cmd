cmd_net/bridge/netfilter/ebt_mark.mod := printf '%s\n'   ebt_mark.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_mark.mod
