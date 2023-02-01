cmd_net/sched/em_canid.mod := printf '%s\n'   em_canid.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_canid.mod
