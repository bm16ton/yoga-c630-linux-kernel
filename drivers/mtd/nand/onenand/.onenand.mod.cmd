cmd_drivers/mtd/nand/onenand/onenand.mod := printf '%s\n'   onenand_base.o onenand_bbt.o | awk '!x[$$0]++ { print("drivers/mtd/nand/onenand/"$$0) }' > drivers/mtd/nand/onenand/onenand.mod
