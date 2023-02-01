cmd_net/sched/cls_flow.mod := printf '%s\n'   cls_flow.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_flow.mod
