cmd_net/sched/act_police.mod := printf '%s\n'   act_police.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_police.mod
