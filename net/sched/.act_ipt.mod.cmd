cmd_net/sched/act_ipt.mod := printf '%s\n'   act_ipt.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_ipt.mod
