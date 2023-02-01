cmd_drivers/md/raid10.mod := printf '%s\n'   raid10.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/raid10.mod
