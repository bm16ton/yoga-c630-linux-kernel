cmd_drivers/mtd/rfd_ftl.mod := printf '%s\n'   rfd_ftl.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/rfd_ftl.mod
