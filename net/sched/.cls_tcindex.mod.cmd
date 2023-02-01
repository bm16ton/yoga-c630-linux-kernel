cmd_net/sched/cls_tcindex.mod := printf '%s\n'   cls_tcindex.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_tcindex.mod
