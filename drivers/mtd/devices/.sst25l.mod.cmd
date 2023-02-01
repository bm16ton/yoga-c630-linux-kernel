cmd_drivers/mtd/devices/sst25l.mod := printf '%s\n'   sst25l.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/sst25l.mod
