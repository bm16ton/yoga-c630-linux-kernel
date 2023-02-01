cmd_net/sched/act_ife.mod := printf '%s\n'   act_ife.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_ife.mod
