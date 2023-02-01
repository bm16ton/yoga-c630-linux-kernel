cmd_net/sched/cls_flower.mod := printf '%s\n'   cls_flower.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_flower.mod
