cmd_net/bridge/netfilter/ebt_redirect.mod := printf '%s\n'   ebt_redirect.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/ebt_redirect.mod
