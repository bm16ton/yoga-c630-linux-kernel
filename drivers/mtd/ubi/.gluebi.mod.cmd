cmd_drivers/mtd/ubi/gluebi.mod := printf '%s\n'   gluebi.o | awk '!x[$$0]++ { print("drivers/mtd/ubi/"$$0) }' > drivers/mtd/ubi/gluebi.mod
