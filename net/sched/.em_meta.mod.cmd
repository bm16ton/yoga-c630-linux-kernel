cmd_net/sched/em_meta.mod := printf '%s\n'   em_meta.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_meta.mod
