cmd_net/sched/sch_cake.mod := printf '%s\n'   sch_cake.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_cake.mod
