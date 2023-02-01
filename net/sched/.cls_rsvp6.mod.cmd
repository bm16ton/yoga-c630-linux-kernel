cmd_net/sched/cls_rsvp6.mod := printf '%s\n'   cls_rsvp6.o | awk '!x[$$0]++ { print("net/sched/"$$0) }' > net/sched/cls_rsvp6.mod
