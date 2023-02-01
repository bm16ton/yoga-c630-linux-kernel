cmd_drivers/mtd/parsers/ofpart.mod := printf '%s\n'   ofpart_core.o | awk '!x[$$0]++ { print("drivers/mtd/parsers/"$$0) }' > drivers/mtd/parsers/ofpart.mod
