cmd_net/sched/sch_mqprio.mod := printf '%s\n'   sch_mqprio.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_mqprio.mod
