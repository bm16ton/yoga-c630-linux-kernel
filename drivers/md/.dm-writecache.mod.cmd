cmd_drivers/md/dm-writecache.mod := printf '%s\n'   dm-writecache.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-writecache.mod
