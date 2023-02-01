cmd_net/netfilter/xt_TEE.mod := printf '%s\n'   xt_TEE.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_TEE.mod
