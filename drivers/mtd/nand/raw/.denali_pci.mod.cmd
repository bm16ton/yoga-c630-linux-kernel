cmd_drivers/mtd/nand/raw/denali_pci.mod := printf '%s\n'   denali_pci.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/denali_pci.mod
