cmd_net/sched/sch_drr.mod := printf '%s\n'   sch_drr.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_drr.mod
