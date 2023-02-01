cmd_net/netfilter/xt_osf.mod := printf '%s\n'   xt_osf.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_osf.mod
