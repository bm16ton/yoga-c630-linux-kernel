cmd_net/sched/sch_ingress.mod := printf '%s\n'   sch_ingress.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_ingress.mod
