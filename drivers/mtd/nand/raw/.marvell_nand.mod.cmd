cmd_drivers/mtd/nand/raw/marvell_nand.mod := printf '%s\n'   marvell_nand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/marvell_nand.mod
