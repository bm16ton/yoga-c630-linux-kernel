cmd_net/sched/sch_sfq.mod := printf '%s\n'   sch_sfq.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_sfq.mod
