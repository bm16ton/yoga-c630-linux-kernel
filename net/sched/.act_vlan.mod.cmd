cmd_net/sched/act_vlan.mod := printf '%s\n'   act_vlan.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_vlan.mod
