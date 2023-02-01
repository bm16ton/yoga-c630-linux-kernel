cmd_drivers/ata/ahci.mod := printf '%s\n'   ahci.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci.mod
