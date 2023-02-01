cmd_drivers/mtd/chips/map_ram.mod := printf '%s\n'   map_ram.o | awk '!x[$$0]++ { print("drivers/mtd/chips/"$$0) }' > drivers/mtd/chips/map_ram.mod
