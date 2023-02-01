cmd_drivers/nvme/host/nvme-fc.mod := printf '%s\n'   fc.o | awk '!x[$$0]++ { print("drivers/nvme/host/"$$0) }' > drivers/nvme/host/nvme-fc.mod
