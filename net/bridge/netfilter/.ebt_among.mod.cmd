cmd_net/bridge/netfilter/ebt_among.mod := printf '%s\n'   ebt_among.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_among.mod
