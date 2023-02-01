cmd_drivers/mtd/devices/block2mtd.mod := printf '%s\n'   block2mtd.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/block2mtd.mod
