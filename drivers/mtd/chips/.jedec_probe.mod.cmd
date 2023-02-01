cmd_drivers/mtd/chips/jedec_probe.mod := printf '%s\n'   jedec_probe.o | awk '!x[$$0]++ { print("drivers/mtd/chips/"$$0) }' > drivers/mtd/chips/jedec_probe.mod
