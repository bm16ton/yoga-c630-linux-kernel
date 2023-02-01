cmd_drivers/mtd/ssfdc.mod := printf '%s\n'   ssfdc.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/ssfdc.mod
