cmd_net/sched/sch_prio.mod := printf '%s\n'   sch_prio.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_prio.mod
