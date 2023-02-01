cmd_net/sched/act_mirred.mod := printf '%s\n'   act_mirred.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_mirred.mod
