cmd_net/sched/em_u32.mod := printf '%s\n'   em_u32.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_u32.mod
