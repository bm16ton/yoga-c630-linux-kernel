cmd_drivers/block/brd.mod := printf '%s\n'   brd.o | awk '!x[$$0]++ { print("drivers/block/"$$0) }' > drivers/block/brd.mod
