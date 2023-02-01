cmd_net/sched/sch_hhf.mod := printf '%s\n'   sch_hhf.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_hhf.mod
