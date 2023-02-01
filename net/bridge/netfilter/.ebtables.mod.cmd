cmd_net/bridge/netfilter/ebtables.mod := printf '%s\n'   ebtables.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebtables.mod
