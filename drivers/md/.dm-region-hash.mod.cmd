cmd_drivers/md/dm-region-hash.mod := printf '%s\n'   dm-region-hash.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-region-hash.mod
