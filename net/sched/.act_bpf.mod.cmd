cmd_net/sched/act_bpf.mod := printf '%s\n'   act_bpf.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_bpf.mod
