cmd_net/sched/act_skbedit.mod := printf '%s\n'   act_skbedit.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_skbedit.mod
