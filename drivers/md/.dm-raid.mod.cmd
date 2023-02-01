cmd_drivers/md/dm-raid.mod := printf '%s\n'   dm-raid.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-raid.mod
