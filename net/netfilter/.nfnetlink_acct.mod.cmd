cmd_net/netfilter/nfnetlink_acct.mod := printf '%s\n'   nfnetlink_acct.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink_acct.mod
