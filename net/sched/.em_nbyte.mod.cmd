cmd_net/sched/em_nbyte.mod := printf '%s\n'   em_nbyte.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_nbyte.mod
