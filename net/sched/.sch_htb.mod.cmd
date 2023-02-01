cmd_net/sched/sch_htb.mod := printf '%s\n'   sch_htb.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/sch_htb.mod
