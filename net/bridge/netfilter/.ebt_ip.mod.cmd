cmd_net/bridge/netfilter/ebt_ip.mod := printf '%s\n'   ebt_ip.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_ip.mod
