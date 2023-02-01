cmd_drivers/mtd/devices/docg3.mod := printf '%s\n'   docg3.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/docg3.mod
