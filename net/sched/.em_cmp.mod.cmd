cmd_net/sched/em_cmp.mod := printf '%s\n'   em_cmp.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_cmp.mod
