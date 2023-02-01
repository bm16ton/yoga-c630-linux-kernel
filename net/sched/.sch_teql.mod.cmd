cmd_net/sched/sch_teql.mod := printf '%s\n'   sch_teql.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_teql.mod
