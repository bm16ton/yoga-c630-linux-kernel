cmd_drivers/mtd/nand/raw/r852.mod := printf '%s\n'   r852.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/r852.mod
