cmd_net/bridge/netfilter/ebt_802_3.mod := printf '%s\n'   ebt_802_3.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_802_3.mod
