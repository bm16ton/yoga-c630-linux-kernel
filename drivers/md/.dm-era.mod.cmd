cmd_drivers/md/dm-era.mod := printf '%s\n'   dm-era-target.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-era.mod
