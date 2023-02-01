cmd_net/netfilter/xt_bpf.mod := printf '%s\n'   xt_bpf.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_bpf.mod
