cmd_drivers/ata/sata_sx4.mod := printf '%s\n'   sata_sx4.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_sx4.mod
