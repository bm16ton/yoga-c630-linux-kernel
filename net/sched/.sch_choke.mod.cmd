cmd_net/sched/sch_choke.mod := printf '%s\n'   sch_choke.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_choke.mod
