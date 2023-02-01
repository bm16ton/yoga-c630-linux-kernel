cmd_net/netfilter/xt_CHECKSUM.mod := printf '%s\n'   xt_CHECKSUM.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_CHECKSUM.mod
