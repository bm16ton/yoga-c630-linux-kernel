cmd_net/sched/sch_qfq.mod := printf '%s\n'   sch_qfq.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_qfq.mod
