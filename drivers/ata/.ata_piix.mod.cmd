cmd_drivers/ata/ata_piix.mod := printf '%s\n'   ata_piix.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ata_piix.mod
