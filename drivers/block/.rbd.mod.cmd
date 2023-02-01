cmd_drivers/block/rbd.mod := printf '%s\n'   rbd.o | awk '!x[$$0]++ { print("drivers/block/"$$0) }' > drivers/block/rbd.mod
