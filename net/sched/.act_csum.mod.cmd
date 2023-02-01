cmd_net/sched/act_csum.mod := printf '%s\n'   act_csum.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_csum.mod
