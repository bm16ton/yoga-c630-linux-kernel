cmd_drivers/mtd/nand/raw/sunxi_nand.mod := printf '%s\n'   sunxi_nand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/sunxi_nand.mod
