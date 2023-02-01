cmd_net/sched/sch_taprio.mod := printf '%s\n'   sch_taprio.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_taprio.mod
