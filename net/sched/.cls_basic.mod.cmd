cmd_net/sched/cls_basic.mod := printf '%s\n'   cls_basic.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_basic.mod
