cmd_drivers/mtd/nand/raw/diskonchip.mod := printf '%s\n'   diskonchip.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/diskonchip.mod
