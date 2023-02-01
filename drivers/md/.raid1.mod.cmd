cmd_drivers/md/raid1.mod := printf '%s\n'   raid1.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/raid1.mod
