cmd_net/sched/cls_matchall.mod := printf '%s\n'   cls_matchall.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_matchall.mod
