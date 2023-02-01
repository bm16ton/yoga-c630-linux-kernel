cmd_drivers/mtd/devices/mtd_dataflash.mod := printf '%s\n'   mtd_dataflash.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/mtd_dataflash.mod
