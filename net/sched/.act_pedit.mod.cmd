cmd_net/sched/act_pedit.mod := printf '%s\n'   act_pedit.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_pedit.mod
