cmd_net/sched/sch_netem.mod := printf '%s\n'   sch_netem.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_netem.mod
