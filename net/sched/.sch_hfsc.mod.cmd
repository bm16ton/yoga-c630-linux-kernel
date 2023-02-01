cmd_net/sched/sch_hfsc.mod := printf '%s\n'   sch_hfsc.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_hfsc.mod
