cmd_net/sched/cls_rsvp.mod := printf '%s\n'   cls_rsvp.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_rsvp.mod
