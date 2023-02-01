cmd_drivers/md/dm-queue-length.mod := printf '%s\n'   dm-ps-queue-length.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-queue-length.mod
