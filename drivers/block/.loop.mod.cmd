cmd_drivers/block/loop.mod := printf '%s\n'   loop.o | awk '!x[$$0]++ { print("drivers/block/"$$0) }' > drivers/block/loop.mod
