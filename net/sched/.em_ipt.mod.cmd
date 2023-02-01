cmd_net/sched/em_ipt.mod := printf '%s\n'   em_ipt.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_ipt.mod
