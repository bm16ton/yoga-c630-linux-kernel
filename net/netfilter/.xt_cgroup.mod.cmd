cmd_net/netfilter/xt_cgroup.mod := printf '%s\n'   xt_cgroup.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_cgroup.mod
