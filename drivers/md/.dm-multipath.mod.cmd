cmd_drivers/md/dm-multipath.mod := printf '%s\n'   dm-path-selector.o dm-mpath.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-multipath.mod
