cmd_net/netfilter/nfnetlink_cthelper.mod := printf '%s\n'   nfnetlink_cthelper.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink_cthelper.mod
