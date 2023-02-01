cmd_net/netfilter/xt_hashlimit.mod := printf '%s\n'   xt_hashlimit.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_hashlimit.mod
