cmd_drivers/mtd/sm_ftl.mod := printf '%s\n'   sm_ftl.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/sm_ftl.mod
