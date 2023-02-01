cmd_drivers/md/multipath.mod := printf '%s\n'   md-multipath.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/multipath.mod
