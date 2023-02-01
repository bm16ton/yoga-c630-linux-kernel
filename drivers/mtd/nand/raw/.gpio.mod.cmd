cmd_drivers/mtd/nand/raw/gpio.mod := printf '%s\n'   gpio.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/gpio.mod
