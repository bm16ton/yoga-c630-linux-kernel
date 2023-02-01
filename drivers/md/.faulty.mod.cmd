cmd_drivers/md/faulty.mod := printf '%s\n'   md-faulty.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/faulty.mod
