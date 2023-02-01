cmd_net/sched/cls_fw.mod := printf '%s\n'   cls_fw.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_fw.mod
