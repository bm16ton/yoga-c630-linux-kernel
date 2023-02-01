cmd_drivers/md/dm-round-robin.mod := printf '%s\n'   dm-ps-round-robin.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-round-robin.mod
