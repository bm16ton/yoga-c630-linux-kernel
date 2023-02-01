cmd_drivers/mtd/parsers/qcomsmempart.mod := printf '%s\n'   qcomsmempart.o | awk '!x[$$0]++ { print("drivers/mtd/parsers/"$$0) }' > drivers/mtd/parsers/qcomsmempart.mod
