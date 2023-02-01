cmd_drivers/mtd/devices/slram.mod := printf '%s\n'   slram.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/slram.mod
