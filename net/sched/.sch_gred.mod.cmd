cmd_net/sched/sch_gred.mod := printf '%s\n'   sch_gred.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_gred.mod
