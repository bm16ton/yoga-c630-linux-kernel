cmd_drivers/md/dm-thin-pool.mod := printf '%s\n'   dm-thin.o dm-thin-metadata.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-thin-pool.mod
