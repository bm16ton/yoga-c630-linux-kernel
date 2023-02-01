cmd_drivers/mtd/parsers/afs.mod := printf '%s\n'   afs.o | awk '!x[$$0]++ { print("drivers/mtd/parsers/"$$0) }' > drivers/mtd/parsers/afs.mod
