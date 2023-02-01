cmd_drivers/md/dm-bufio.mod := printf '%s\n'   dm-bufio.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-bufio.mod
