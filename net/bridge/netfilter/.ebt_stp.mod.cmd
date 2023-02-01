cmd_net/bridge/netfilter/ebt_stp.mod := printf '%s\n'   ebt_stp.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_stp.mod
