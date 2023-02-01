cmd_net/bridge/netfilter/ebtable_filter.mod := printf '%s\n'   ebtable_filter.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebtable_filter.mod
