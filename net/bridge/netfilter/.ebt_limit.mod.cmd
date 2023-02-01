cmd_net/bridge/netfilter/ebt_limit.mod := printf '%s\n'   ebt_limit.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_limit.mod
