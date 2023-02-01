cmd_drivers/md/dm-verity.mod := printf '%s\n'   dm-verity-verify-sig.o dm-verity-target.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-verity.mod
