cmd_drivers/mtd/nand/raw/qcom_nandc.mod := printf '%s\n'   qcom_nandc.o | awk '!x[$$0]++ { print("drivers/mtd/nand/raw/"$$0) }' > drivers/mtd/nand/raw/qcom_nandc.mod
