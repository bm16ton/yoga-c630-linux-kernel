cmd_drivers/mtd/nand/raw/sm_common.mod := printf '%s\n'   sm_common.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/sm_common.mod
