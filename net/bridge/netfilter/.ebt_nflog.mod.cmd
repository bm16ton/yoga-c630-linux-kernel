cmd_net/bridge/netfilter/ebt_nflog.mod := printf '%s\n'   ebt_nflog.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_nflog.mod
