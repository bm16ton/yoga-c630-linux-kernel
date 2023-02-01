cmd_drivers/ata/ata_generic.mod := printf '%s\n'   ata_generic.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ata_generic.mod
