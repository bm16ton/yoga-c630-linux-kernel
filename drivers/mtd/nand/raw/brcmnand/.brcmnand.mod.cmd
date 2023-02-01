cmd_drivers/mtd/nand/raw/brcmnand/brcmnand.mod := printf '%s\n'   brcmnand.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/brcmnand/"$$0) }' > drivers/mtd/nand/raw/brcmnand/brcmnand.mod
