cmd_drivers/mtd/mtdblock_ro.mod := printf '%s\n'   mtdblock_ro.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/mtdblock_ro.mod
