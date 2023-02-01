cmd_net/netfilter/nfnetlink_osf.mod := printf '%s\n'   nfnetlink_osf.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink_osf.mod
