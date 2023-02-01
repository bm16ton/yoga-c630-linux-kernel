cmd_drivers/md/raid0.mod := printf '%s\n'   raid0.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/raid0.mod
