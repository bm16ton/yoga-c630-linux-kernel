cmd_net/sched/sch_atm.mod := printf '%s\n'   sch_atm.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_atm.mod
