cmd_drivers/mtd/nand/onenand/generic.mod := printf '%s\n'   generic.o | awk '!x[$$0]++ { print("drivers/mtd/nand/onenand/"$$0) }' > drivers/mtd/nand/onenand/generic.mod
