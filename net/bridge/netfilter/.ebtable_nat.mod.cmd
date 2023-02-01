cmd_net/bridge/netfilter/ebtable_nat.mod := printf '%s\n'   ebtable_nat.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebtable_nat.mod
