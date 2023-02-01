cmd_net/sched/cls_cgroup.mod := printf '%s\n'   cls_cgroup.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_cgroup.mod
