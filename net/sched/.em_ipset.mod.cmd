cmd_net/sched/em_ipset.mod := printf '%s\n'   em_ipset.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_ipset.mod
