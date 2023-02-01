cmd_drivers/md/dm-flakey.mod := printf '%s\n'   dm-flakey.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-flakey.mod
