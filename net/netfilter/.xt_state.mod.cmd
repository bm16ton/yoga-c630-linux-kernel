cmd_net/netfilter/xt_state.mod := printf '%s\n'   xt_state.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_state.mod
