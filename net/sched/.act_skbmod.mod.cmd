cmd_net/sched/act_skbmod.mod := printf '%s\n'   act_skbmod.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_skbmod.mod
