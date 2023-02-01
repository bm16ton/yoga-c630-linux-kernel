cmd_drivers/mtd/ftl.mod := printf '%s\n'   ftl.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/ftl.mod
