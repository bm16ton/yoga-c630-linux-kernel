cmd_drivers/ata/sata_sis.mod := printf '%s\n'   sata_sis.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_sis.mod
