cmd_drivers/mtd/nand/raw/tegra_nand.mod := printf '%s\n'   tegra_nand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/tegra_nand.mod
