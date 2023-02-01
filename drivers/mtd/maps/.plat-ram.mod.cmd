cmd_drivers/mtd/maps/plat-ram.mod := printf '%s\n'   plat-ram.o | awk '!x[$$0]++ { print("drivers/mtd/maps/"$$0) }' > drivers/mtd/maps/plat-ram.mod
