cmd_drivers/nvme/host/nvme-rdma.mod := printf '%s\n'   rdma.o | awk '!x[$$0]++ { print("drivers/nvme/host/"$$0) }' > drivers/nvme/host/nvme-rdma.mod
