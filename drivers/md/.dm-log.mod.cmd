cmd_drivers/md/dm-log.mod := printf '%s\n'   dm-log.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-log.mod
