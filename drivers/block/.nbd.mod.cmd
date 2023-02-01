cmd_drivers/block/nbd.mod := printf '%s\n'   nbd.o | awk '!x[$$0]++ { print("drivers/block/"$$0) }' > drivers/block/nbd.mod
