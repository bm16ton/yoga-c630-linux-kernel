cmd_drivers/md/dm-crypt.mod := printf '%s\n'   dm-crypt.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-crypt.mod
