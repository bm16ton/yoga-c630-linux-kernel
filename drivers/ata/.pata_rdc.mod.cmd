cmd_drivers/ata/pata_rdc.mod := printf '%s\n'   pata_rdc.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_rdc.mod
