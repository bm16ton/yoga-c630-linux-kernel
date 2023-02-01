cmd_drivers/md/dm-unstripe.mod := printf '%s\n'   dm-unstripe.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-unstripe.mod
