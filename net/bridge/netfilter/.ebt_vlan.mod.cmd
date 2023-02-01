cmd_net/bridge/netfilter/ebt_vlan.mod := printf '%s\n'   ebt_vlan.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_vlan.mod
