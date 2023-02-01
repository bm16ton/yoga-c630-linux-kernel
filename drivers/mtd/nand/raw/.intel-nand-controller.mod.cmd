cmd_drivers/mtd/nand/raw/intel-nand-controller.mod := printf '%s\n'   intel-nand-controller.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/intel-nand-controller.mod
