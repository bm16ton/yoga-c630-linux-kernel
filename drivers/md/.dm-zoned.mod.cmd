cmd_drivers/md/dm-zoned.mod := printf '%s\n'   dm-zoned-target.o dm-zoned-metadata.o dm-zoned-reclaim.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-zoned.mod
