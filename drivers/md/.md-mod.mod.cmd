cmd_drivers/md/md-mod.mod := printf '%s\n'   md.o md-bitmap.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/md-mod.mod
