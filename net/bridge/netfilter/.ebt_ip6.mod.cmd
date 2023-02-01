cmd_net/bridge/netfilter/ebt_ip6.mod := printf '%s\n'   ebt_ip6.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_ip6.mod
