cmd_net/sched/sch_cbq.mod := printf '%s\n'   sch_cbq.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_cbq.mod
