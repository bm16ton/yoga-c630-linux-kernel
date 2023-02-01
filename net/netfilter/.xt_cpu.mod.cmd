cmd_net/netfilter/xt_cpu.mod := printf '%s\n'   xt_cpu.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_cpu.mod
