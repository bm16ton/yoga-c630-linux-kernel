cmd_drivers/md/dm-log-writes.mod := printf '%s\n'   dm-log-writes.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-log-writes.mod
