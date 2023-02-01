cmd_drivers/nvme/target/nvmet-rdma.mod := printf '%s\n'   rdma.o | awk '!x[$$0]++ { print("drivers/nvme/target/"$$0) }' > drivers/nvme/target/nvmet-rdma.mod
