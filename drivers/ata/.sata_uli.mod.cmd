cmd_drivers/ata/sata_uli.mod := printf '%s\n'   sata_uli.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_uli.mod
