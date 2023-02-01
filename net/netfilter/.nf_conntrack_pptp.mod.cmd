cmd_net/netfilter/nf_conntrack_pptp.mod := printf '%s\n'   nf_conntrack_pptp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_conntrack_pptp.mod
