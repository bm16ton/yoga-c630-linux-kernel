cmd_net/netfilter/nfnetlink_log.mod := printf '%s\n'   nfnetlink_log.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink_log.mod
