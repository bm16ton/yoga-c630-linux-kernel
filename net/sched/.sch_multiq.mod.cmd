cmd_net/sched/sch_multiq.mod := printf '%s\n'   sch_multiq.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_multiq.mod
