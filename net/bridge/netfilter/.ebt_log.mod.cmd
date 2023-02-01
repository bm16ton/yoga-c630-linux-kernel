cmd_net/bridge/netfilter/ebt_log.mod := printf '%s\n'   ebt_log.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_log.mod
