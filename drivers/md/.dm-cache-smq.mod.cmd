cmd_drivers/md/dm-cache-smq.mod := printf '%s\n'   dm-cache-policy-smq.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-cache-smq.mod
