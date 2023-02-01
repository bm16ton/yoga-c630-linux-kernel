cmd_net/sched/act_gact.mod := printf '%s\n'   act_gact.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_gact.mod
