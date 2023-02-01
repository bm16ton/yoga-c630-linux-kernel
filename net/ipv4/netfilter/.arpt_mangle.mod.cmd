cmd_net/ipv4/netfilter/arpt_mangle.mod := printf '%s\n'   arpt_mangle.o | awk '!x[$$0]++ { print("net/ipv4/netfilter/"$$0) }' > net/ipv4/netfilter/arpt_mangle.mod
