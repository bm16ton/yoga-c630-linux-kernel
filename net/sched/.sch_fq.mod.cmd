cmd_net/sched/sch_fq.mod := printf '%s\n'   sch_fq.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_fq.mod
