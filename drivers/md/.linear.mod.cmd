cmd_drivers/md/linear.mod := printf '%s\n'   md-linear.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/linear.mod
