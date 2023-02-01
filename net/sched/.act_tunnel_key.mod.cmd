cmd_net/sched/act_tunnel_key.mod := printf '%s\n'   act_tunnel_key.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_tunnel_key.mod
