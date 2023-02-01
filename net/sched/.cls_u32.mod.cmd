cmd_net/sched/cls_u32.mod := printf '%s\n'   cls_u32.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_u32.mod
