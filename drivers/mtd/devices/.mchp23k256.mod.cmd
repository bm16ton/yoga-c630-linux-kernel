cmd_drivers/mtd/devices/mchp23k256.mod := printf '%s\n'   mchp23k256.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/mchp23k256.mod
