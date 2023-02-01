cmd_drivers/mtd/inftl.mod := printf '%s\n'   inftlcore.o inftlmount.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/inftl.mod
