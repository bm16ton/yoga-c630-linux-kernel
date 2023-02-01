cmd_net/sched/sch_dsmark.mod := printf '%s\n'   sch_dsmark.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_dsmark.mod
