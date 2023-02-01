cmd_net/sched/sch_red.mod := printf '%s\n'   sch_red.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_red.mod
