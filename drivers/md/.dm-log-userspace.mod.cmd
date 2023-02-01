cmd_drivers/md/dm-log-userspace.mod := printf '%s\n'   dm-log-userspace-base.o dm-log-userspace-transfer.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-log-userspace.mod
