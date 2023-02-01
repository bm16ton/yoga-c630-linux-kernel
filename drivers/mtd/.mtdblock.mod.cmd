cmd_drivers/mtd/mtdblock.mod := printf '%s\n'   mtdblock.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/mtdblock.mod
