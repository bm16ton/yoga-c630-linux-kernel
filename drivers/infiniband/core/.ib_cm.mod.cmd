cmd_drivers/infiniband/core/ib_cm.mod := printf '%s\n'   cm.o cm_trace.o | awk '!x[$$0]++ { print("drivers/infiniband/core/"$$0) }' > drivers/infiniband/core/ib_cm.mod
