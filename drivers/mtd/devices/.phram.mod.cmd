cmd_drivers/mtd/devices/phram.mod := printf '%s\n'   phram.o | awk '!x[$$0]++ { print("drivers/mtd/devices/"$$0) }' > drivers/mtd/devices/phram.mod
