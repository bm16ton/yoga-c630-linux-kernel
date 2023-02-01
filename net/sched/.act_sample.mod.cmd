cmd_net/sched/act_sample.mod := printf '%s\n'   act_sample.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_sample.mod
