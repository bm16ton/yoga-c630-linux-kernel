cmd_drivers/mtd/chips/map_rom.mod := printf '%s\n'   map_rom.o | awk '!x[$$0]++ { print("drivers/mtd/chips/"$$0) }' > drivers/mtd/chips/map_rom.mod
