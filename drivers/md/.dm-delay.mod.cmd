cmd_drivers/md/dm-delay.mod := printf '%s\n'   dm-delay.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-delay.mod
