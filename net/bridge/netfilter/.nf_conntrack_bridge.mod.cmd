cmd_net/bridge/netfilter/nf_conntrack_bridge.mod := printf '%s\n'   nf_conntrack_bridge.o | awk '!x[$$0]++ { print("net/bridge/netfilter/"$$0) }' > net/bridge/netfilter/nf_conntrack_bridge.mod
