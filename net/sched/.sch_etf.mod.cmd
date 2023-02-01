cmd_net/sched/sch_etf.mod := printf '%s\n'   sch_etf.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_etf.mod
