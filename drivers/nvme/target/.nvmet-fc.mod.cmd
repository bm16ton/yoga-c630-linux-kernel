cmd_drivers/nvme/target/nvmet-fc.mod := printf '%s\n'   fc.o | awk '!x[$$0]++ { print("drivers/nvme/target/"$$0) }' > drivers/nvme/target/nvmet-fc.mod
