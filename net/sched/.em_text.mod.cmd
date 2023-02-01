cmd_net/sched/em_text.mod := printf '%s\n'   em_text.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/em_text.mod
