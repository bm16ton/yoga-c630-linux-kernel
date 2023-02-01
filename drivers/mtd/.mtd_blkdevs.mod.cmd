cmd_drivers/mtd/mtd_blkdevs.mod := printf '%s\n'   mtd_blkdevs.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/mtd_blkdevs.mod
