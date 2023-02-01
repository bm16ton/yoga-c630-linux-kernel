cmd_drivers/md/dm-zero.mod := printf '%s\n'   dm-zero.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-zero.mod
