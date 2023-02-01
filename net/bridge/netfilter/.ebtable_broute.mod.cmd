cmd_net/bridge/netfilter/ebtable_broute.mod := printf '%s\n'   ebtable_broute.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebtable_broute.mod
