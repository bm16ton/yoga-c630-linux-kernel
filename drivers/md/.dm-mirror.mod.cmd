cmd_drivers/md/dm-mirror.mod := printf '%s\n'   dm-raid1.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-mirror.mod
