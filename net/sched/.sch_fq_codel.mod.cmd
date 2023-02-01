cmd_net/sched/sch_fq_codel.mod := printf '%s\n'   sch_fq_codel.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_fq_codel.mod
