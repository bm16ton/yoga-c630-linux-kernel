cmd_drivers/ata/sata_via.mod := printf '%s\n'   sata_via.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_via.mod
