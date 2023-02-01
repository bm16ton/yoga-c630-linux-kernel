cmd_net/sched/act_nat.mod := printf '%s\n'   act_nat.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_nat.mod
