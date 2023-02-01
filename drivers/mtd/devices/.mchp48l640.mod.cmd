cmd_drivers/mtd/devices/mchp48l640.mod := printf '%s\n'   mchp48l640.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/mchp48l640.mod
