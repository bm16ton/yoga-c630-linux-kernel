cmd_net/sched/sch_tbf.mod := printf '%s\n'   sch_tbf.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_tbf.mod
