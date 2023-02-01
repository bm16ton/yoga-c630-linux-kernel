cmd_net/netfilter/xt_HL.mod := printf '%s\n'   xt_HL.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_HL.mod
