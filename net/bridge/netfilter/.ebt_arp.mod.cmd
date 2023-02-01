cmd_net/bridge/netfilter/ebt_arp.mod := printf '%s\n'   ebt_arp.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_arp.mod
