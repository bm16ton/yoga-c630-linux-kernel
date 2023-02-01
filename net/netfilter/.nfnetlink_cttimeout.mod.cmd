cmd_net/netfilter/nfnetlink_cttimeout.mod := printf '%s\n'   nfnetlink_cttimeout.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nfnetlink_cttimeout.mod
