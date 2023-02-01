cmd_drivers/mtd/nand/raw/denali_dt.mod := printf '%s\n'   denali_dt.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/denali_dt.mod
