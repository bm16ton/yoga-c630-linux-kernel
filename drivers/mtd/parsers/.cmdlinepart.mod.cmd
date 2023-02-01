cmd_drivers/mtd/parsers/cmdlinepart.mod := printf '%s\n'   cmdlinepart.o | awk '!x[$$0]++ { print("drivers/mtd/parsers/"$$0) }' > drivers/mtd/parsers/cmdlinepart.mod
