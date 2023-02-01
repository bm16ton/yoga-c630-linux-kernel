cmd_drivers/md/dm-integrity.mod := printf '%s\n'   dm-integrity.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-integrity.mod
