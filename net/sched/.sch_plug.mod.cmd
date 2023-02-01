cmd_net/sched/sch_plug.mod := printf '%s\n'   sch_plug.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_plug.mod
