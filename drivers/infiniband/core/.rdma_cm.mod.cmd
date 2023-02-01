cmd_drivers/infiniband/core/rdma_cm.mod := printf '%s\n'   cma.o cma_trace.o cma_configfs.o | awk '!x[$$0]++ { print("drivers/infiniband/core/"$$0) }' > drivers/infiniband/core/rdma_cm.mod
