cmd_drivers/mtd/nand/raw/denali.mod := printf '%s\n'   denali.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/denali.mod
