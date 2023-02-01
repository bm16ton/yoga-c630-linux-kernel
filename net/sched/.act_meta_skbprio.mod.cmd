cmd_net/sched/act_meta_skbprio.mod := printf '%s\n'   act_meta_skbprio.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_meta_skbprio.mod
