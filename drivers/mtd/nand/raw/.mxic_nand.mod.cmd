cmd_drivers/mtd/nand/raw/mxic_nand.mod := printf '%s\n'   mxic_nand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/mxic_nand.mod
