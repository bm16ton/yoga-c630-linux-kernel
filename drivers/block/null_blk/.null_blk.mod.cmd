cmd_drivers/block/null_blk/null_blk.mod := printf '%s\n'   main.o trace.o zoned.o | awk '!x[$$0]++ { print("drivers/block/null_blk/"$$0) }' > drivers/block/null_blk/null_blk.mod
