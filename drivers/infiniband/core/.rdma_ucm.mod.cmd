cmd_drivers/infiniband/core/rdma_ucm.mod := printf '%s\n'   ucma.o | awk '!x[$$0]++ { print("drivers/infiniband/core/"$$0) }' > drivers/infiniband/core/rdma_ucm.mod
