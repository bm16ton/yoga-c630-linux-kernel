cmd_drivers/nvme/host/nvme-fabrics.mod := printf '%s\n'   fabrics.o | awk '!x[$$0]++ { print("drivers/nvme/host/"$$0) }' > drivers/nvme/host/nvme-fabrics.mod
