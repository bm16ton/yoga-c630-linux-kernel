cmd_drivers/md/dm-switch.mod := printf '%s\n'   dm-switch.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-switch.mod
