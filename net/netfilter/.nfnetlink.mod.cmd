cmd_net/netfilter/nfnetlink.mod := printf '%s\n'   nfnetlink.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink.mod
