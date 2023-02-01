cmd_net/sched/cls_route.mod := printf '%s\n'   cls_route.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_route.mod
