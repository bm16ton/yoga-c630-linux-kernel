cmd_drivers/mtd/nand/raw/plat_nand.mod := printf '%s\n'   plat_nand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/plat_nand.mod
