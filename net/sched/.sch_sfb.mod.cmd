cmd_net/sched/sch_sfb.mod := printf '%s\n'   sch_sfb.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_sfb.mod
