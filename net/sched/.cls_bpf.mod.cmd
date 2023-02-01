cmd_net/sched/cls_bpf.mod := printf '%s\n'   cls_bpf.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_bpf.mod
