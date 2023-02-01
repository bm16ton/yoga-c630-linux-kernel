cmd_drivers/nvme/host/nvme.mod := printf '%s\n'   pci.o | awk '!x[$$0]++ { print("drivers/nvme/host/"$$0) }' > drivers/nvme/host/nvme.mod
