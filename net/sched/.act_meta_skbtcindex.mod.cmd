cmd_net/sched/act_meta_skbtcindex.mod := printf '%s\n'   act_meta_skbtcindex.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/act_meta_skbtcindex.mod
