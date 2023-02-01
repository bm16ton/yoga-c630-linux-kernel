cmd_net/sched/act_simple.mod := printf '%s\n'   act_simple.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_simple.mod
