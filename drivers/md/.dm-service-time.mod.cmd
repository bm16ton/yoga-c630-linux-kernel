cmd_drivers/md/dm-service-time.mod := printf '%s\n'   dm-ps-service-time.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-service-time.mod
