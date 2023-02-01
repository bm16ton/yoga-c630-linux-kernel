cmd_net/sched/sch_codel.mod := printf '%s\n'   sch_codel.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_codel.mod
