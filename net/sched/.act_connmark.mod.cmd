cmd_net/sched/act_connmark.mod := printf '%s\n'   act_connmark.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_connmark.mod
