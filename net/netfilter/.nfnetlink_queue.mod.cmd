cmd_net/netfilter/nfnetlink_queue.mod := printf '%s\n'   nfnetlink_queue.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink_queue.mod
