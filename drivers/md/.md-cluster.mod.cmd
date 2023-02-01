cmd_drivers/md/md-cluster.mod := printf '%s\n'   md-cluster.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/md-cluster.mod
