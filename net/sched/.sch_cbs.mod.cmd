cmd_net/sched/sch_cbs.mod := printf '%s\n'   sch_cbs.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_cbs.mod
